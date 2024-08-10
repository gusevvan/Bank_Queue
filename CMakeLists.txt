cmake_minimum_required(VERSION 3.22)
project(bank_queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(bank_queue main.cpp)

file(COPY ./example.json DESTINATION ".")
