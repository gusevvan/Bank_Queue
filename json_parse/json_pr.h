#include <iostream>
#include <cstdio>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "../include/client.h"
#include "../include/department.h"
#include "../include/exceptions.h"


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
            if (d.HasParseError()) {
                throw JSONIncorrectFormat();
            }
            Value const &v(d);
            if (!v.HasMember("departments") || !v.HasMember("clients") || v.MemberCount() > 2) {
                throw JSONIncorrectFormat();
            }
            Value& departments_parsed = d["departments"];
            Value& clients_parsed = d["clients"];

            if (!departments_parsed.IsArray() || !clients_parsed.IsArray()) {
                throw JSONIncorrectFormat();
            }
            
            int num_departments = departments_parsed.GetArray().Size();

            for (int i = 0; i < num_departments; ++i) {
                Value& cur_department = d["departments"][i];
                if (!cur_department.HasMember("name") || !cur_department.HasMember("employees") || cur_department.MemberCount() > 2 ||
                    !cur_department["name"].IsString() || !cur_department["employees"].IsInt()) {
                    throw JSONIncorrectFormat();
                }
                Department new_department(cur_department["name"].GetString(), cur_department["employees"].GetInt());
                departments.push_back(new_department);
            }


            int num_clients = clients_parsed.GetArray().Size();
            for (int i = 0; i < num_clients; ++i) {
                Value& cur_client = d["clients"][i];
                if (!cur_client.HasMember("name") || !cur_client.HasMember("time") || !cur_client.HasMember("priority") ||
                    !cur_client.HasMember("departments") || cur_client.MemberCount() > 4 ||
                    !cur_client["name"].IsString() || !cur_client["time"].IsInt() ||
                    !cur_client["priority"].IsInt() || !cur_client["departments"].IsArray()) {
                    throw JSONIncorrectFormat();
                }
                Value& cur_client_departments_parsed = d["clients"][i]["departments"];
                int num_cur_departments = cur_client_departments_parsed.GetArray().Size();
                std::vector<std::string> cur_client_departments;
                for (int j = 0; j < num_cur_departments; ++j) {
                    if (!d["clients"][i]["departments"][j].IsString()) {
                        throw JSONIncorrectFormat();
                    }
                    cur_client_departments.push_back(d["clients"][i]["departments"][j].GetString());
                }
                Client new_client(d["clients"][i]["name"].GetString(), d["clients"][i]["time"].GetInt(),
                                d["clients"][i]["priority"].GetInt(), cur_client_departments);
                clients.push_back(new_client);
            }
        }
        
        ~JsonParser() = default;
    };
}
 