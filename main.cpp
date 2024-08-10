#include <iostream>
#include <vector>
#include "include/client.h"
#include "include/department.h"
#include "include/bank.h"
#include "json_parse/json_pr.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "You dont enter path to input json\n";
        return 0;
    }
    std::vector<Client> clients;
    std::vector<Department> departments;
    rapidjson::JsonParser parser(argv[1]);
    parser.get_input(clients, departments);
    Bank bank(clients, departments);
    bank.simulate();
}
