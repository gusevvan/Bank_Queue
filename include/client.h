#pragma once
#include <iostream>
#include <queue>
#include <chrono>

class Client {

private:
    std::string _name;
    int _serve_time;
    std::chrono::time_point<std::chrono::system_clock> _start_time = std::chrono::system_clock::now();
    int _priority;
    std::queue<std::string> _department_names;

public:
    Client(const std::string& name, int time, int priority, const std::vector<std::string>& department_names) {
        _name = name;
        _serve_time = time;
        _start_time = std::chrono::system_clock::now();
        _priority = priority;
        for (auto& department_name: department_names) 
            _department_names.push(department_name);
    }

    std::string get_name() {
        return _name;
    }

    void reload_time() {
        _start_time = std::chrono::system_clock::now();
    }

    std::chrono::time_point<std::chrono::system_clock> get_start_time() {
        return _start_time;
    }

    int get_time() {
        return _serve_time;
    }

    int get_priority() {
        return _priority;
    }

    bool is_served() {
        std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = current_time - _start_time;
        return elapsed_seconds.count() * 1000 >= _serve_time;
    }

    std::string get_current_department_name() {
        return _department_names.front();
    }

    bool update_department() {
        _department_names.pop();
        return _department_names.size() == 0;
    }

    ~Client() = default;

};
