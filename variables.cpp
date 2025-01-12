#include "variables.hpp"

void variables::add(std::string name, long double value) {
    _my_variables[name] = value;
}

long double variables::get(std::string name) {
    return _my_variables[name];
}

namespace global {
    variables var;
}
