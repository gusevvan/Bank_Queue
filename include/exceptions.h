#pragma once
#include <iostream>


class JSONNotEntered: public std::exception {
public:
    std::string what () {
        return "Exception: JSON file not entered\n";
    }
};

class JSONNotFound: public std::exception {
public:
    std::string what () {
        return "Exception: JSON file not found\n";
    }
};

class JSONIncorrectFormat: public std::exception {
public:
    std::string what () {
        return "Exception: JSON file is incorrect\n";
    }
};
