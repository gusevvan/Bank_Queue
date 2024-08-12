#pragma once
#include <queue>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include "client.h"
#include "logger.h"

class Department {

private:
    std::string _name;
    std::map<int, std::queue<Client>> _queues{};
    std::vector<Client> _served_clients{};
    int _employees;

public:
    Department() = default;

    Department(const std::string& name, int employees) {
        _name = name;
        _employees = employees;
    }
    
    std::string get_name() {
        return _name;
    }

    int num_left_clients() {
        int counter = _served_clients.size();
        for (auto& [priority, pr_queue] : _queues) {
            counter += pr_queue.size();
        }
        return counter;
    }

    void add_client(Client& client) {
        timelog::logger.dep_come(client.get_name(), _name);
        if (_queues.find(client.get_priority()) == _queues.end()) {
            std::queue<Client> queue;
            _queues[client.get_priority()] = queue;
        }
        _queues[client.get_priority()].push(client);
        start();
    }

    void start() {
        for (auto& [priority, pr_queue]: _queues) {
            while (_served_clients.size() < _employees && pr_queue.size() > 0) {
                timelog::logger.start_serve(pr_queue.front().get_name(), _name);
                pr_queue.front().reload_time();
                _served_clients.push_back(pr_queue.front());
                pr_queue.pop();
            }
        }
    }

    std::vector<Client> update_clients() {
        std::vector<Client> ended{};
        for (int i = 0; i < _served_clients.size(); ++i) {
            if (_served_clients[i].is_served()) {
                ended.push_back(_served_clients[i]);
                timelog::logger.dep_left(_served_clients[i].get_name(), _name);
                _served_clients.erase(_served_clients.begin() + i--);
            }
        }
        start();
        return ended;
    }


    int time_to_next() {
        int min_time = INT_MAX;
        std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
        for (auto& client: _served_clients) {
            std::chrono::duration<double> elapsed_seconds = current_time - client.get_start_time();
            min_time = std::min(min_time, client.get_time() - int(elapsed_seconds.count() * 1000));
        }
        return min_time;
    } 

    ~Department() = default;
};
