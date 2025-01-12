#pragma once
#include <string>
#include <map>
#include <unordered_map>

class variables {
private:
    std::unordered_map<std::string,long double> _my_variables;
public:
    void add(std::string name, long double value);
    long double get(std::string name);
};

namespace global {
    extern variables var;
}
