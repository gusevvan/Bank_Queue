#pragma once
#include <queue>
#include <iostream>
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
        for (int i = 1; i <= 5; ++i) {
            std::queue<Client> queue;
            _queues[i]  = queue;
        }
    }
    
    std::string get_name() {
        return _name;
    }

    int num_left_clients() {
        int counter = _served_clients.size();
        for (auto& [key, val] : _queues)
        {
            counter += val.size();
        }
        return counter;
    }

    void add_client(Client& client) {
        timelog::logger.dep_come(client.get_name(), _name);
        _queues[client.get_priority()].push(client);
    }

    void start() {
        for (int i = 1; i <= 5; ++i) {
            while (_served_clients.size() < _employees && _queues[i].size() > 0) {
                timelog::logger.start_serve(_queues[i].front().get_name(), _name);
                _queues[i].front().reload_time();
                _served_clients.push_back(_queues[i].front());
                _queues[i].pop();
            }
        }
    }

    std::vector<Client> update_clients() {
        std::vector<Client> ended{};
        for (int i = 0; i < _served_clients.size(); ++i) {
            if (_served_clients[i].is_served()) {
                ended.push_back(_served_clients[i]);
                _served_clients.erase(_served_clients.begin() + i--);
            }
        }
        start();
        return ended;
    }

    ~Department() = default;
};
