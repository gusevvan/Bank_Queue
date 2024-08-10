#pragma once
#include <iostream>
#include <map>
#include <vector> 
#include "client.h"
#include "department.h"
#include "logger.h"

class Bank {

private:
    std::map<std::string, Department> _departments;
    std::vector<Client> _clients;

public:
    Bank(std::vector<Client>& clients, std::vector<Department>& departments) {
        for (auto& department: departments) {
            _departments[department.get_name()] = department;
        }
        _clients = clients;
    }

    void simulate() {
        timelog::logger.bank_start();
        for (auto& client: _clients) {
            _departments[client.get_current_department_name()].add_client(client);
        }
        for (auto& [name, department]: _departments) {
            department.start();
        }
        while (true) {
            for (auto& [name, department]: _departments) {
                std::vector<Client> ended = department.update_clients();
                for (auto& client: ended) {
                    timelog::logger.dep_left(client.get_name(), department.get_name());
                    bool is_empty = client.update_department();
                    if (!is_empty) {
                        _departments[client.get_current_department_name()].add_client(client);
                    } else {
                        timelog::logger.bank_left(client.get_name());
                    }
                }
            }
            int num_in_queues = 0;
            for (auto& [name, department]: _departments) {
                num_in_queues += department.num_left_clients();
            }
            if (num_in_queues == 0) {
                break;
            }
        }
        timelog::logger.bank_close(); 
    }

    ~Bank() = default;
};
