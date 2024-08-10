#include <iostream>
#include <vector>
#include <sys/stat.h>
#include "include/client.h"
#include "include/department.h"
#include "include/bank.h"
#include "json_parse/json_pr.h"
#include "include/exceptions.h"


int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            throw JSONNotEntered();
        }
        struct stat buffer;   
        if (stat (argv[1], &buffer) == -1) {
            throw JSONNotFound();
        } 
        std::vector<Client> clients;
        std::vector<Department> departments;
        rapidjson::JsonParser parser(argv[1]);
        parser.get_input(clients, departments);
        Bank bank(clients, departments);
        bank.simulate();
    } catch (JSONNotEntered jne) {
        std::cout << jne.what();
    } catch (JSONNotFound jnf) {
        std::cout << jnf.what();
    } catch (JSONIncorrectFormat jif) {
        std::cout << jif.what();
    }
}
