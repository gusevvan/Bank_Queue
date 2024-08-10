#pragma once
#include <iostream>
#include <chrono>
#include <ctime>    
#include <iomanip>

namespace timelog {
    class TimeLogger {
    public:
        TimeLogger() = default;

        void print_timestamp() {
            std::time_t now = time(0);

            tm *ltm = localtime(&now);

            int year = 1900 + ltm->tm_year;
            int month = 1 + ltm->tm_mon;
            int day = ltm->tm_mday;
            int hour = ltm->tm_hour;
            int min = ltm->tm_min;
            int sec = ltm->tm_sec;
            long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000;

            std::cout << "[" << year << "-";
            std::cout << std::setfill('0') << std::setw(2) << month << "-";
            std::cout << std::setfill('0') << std::setw(2) << day << " ";
            std::cout << std::setfill('0') << std::setw(2) << hour << ":";
            std::cout << std::setfill('0') << std::setw(2) << min << ":";
            std::cout << std::setfill('0') << std::setw(2) << sec << ".";
            std::cout << std::setfill('0') << std::setw(3) << ms << "]";
        }

        void bank_start() {
            print_timestamp();
            std::cout << " Bank opened\n";
        }

        void dep_come(std::string client_name, std::string dep_name) {
            print_timestamp();
            std::cout << " Client " << client_name << " came to the department " << dep_name << "\n";
        }

        void start_serve(std::string client_name, std::string dep_name) {
            print_timestamp();
            std::cout << " Client " << client_name << " is served by the department " << dep_name << "\n";
        }

        void dep_left(std::string client_name, std::string dep_name) {
            print_timestamp();
            std::cout << " Client " << client_name << " left the department " << dep_name << "\n";
        }

        void bank_left(std::string client_name) { 
            print_timestamp();
            std::cout << " Client " << client_name << " left the bank\n";
        }

        void bank_close() {
            print_timestamp();
            std::cout << " Bank closed\n";
        }

        ~TimeLogger() = default;
    };

    TimeLogger logger;
}
