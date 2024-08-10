#include <iostream>
#include <cstdio>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "../include/client.h"
#include "../include/department.h"


namespace rapidjson {
    class JsonParser {
    private:
        std::string _json_path;
    public:
        JsonParser(const std::string& json_path) {
            _json_path = json_path;
        }

        void get_input(std::vector<Client>& clients, std::vector<Department>& departments) {
            FILE* fp = fopen(_json_path.c_str(), "rb");

            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            
            Document d;
            d.ParseStream(is);
            Value& departments_parsed = d["departments"];
            int num_departments = departments_parsed.GetArray().Size();

            for (int i = 0; i < num_departments; ++i) {
                Department cur_department(d["departments"][i]["name"].GetString(), d["departments"][i]["employees"].GetInt());
                departments.push_back(cur_department);
            }

            Value& clients_parsed = d["clients"];
            int num_clients = departments_parsed.GetArray().Size();
            for (int i = 0; i < num_clients; ++i) {
                Value& cur_client_departments_parsed = d["clients"][i]["departments"];
                int num_cur_departments = cur_client_departments_parsed.GetArray().Size();
                std::vector<std::string> cur_client_departments;
                for (int j = 0; j < num_cur_departments; ++j) {
                    cur_client_departments.push_back(d["clients"][i]["departments"][j].GetString());
                }
                Client cur_client(d["clients"][i]["name"].GetString(), d["clients"][i]["time"].GetInt(),
                                d["clients"][i]["priority"].GetInt(), cur_client_departments);
                clients.push_back(cur_client);
            }
        }
    };
}
