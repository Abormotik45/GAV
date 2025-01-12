#pragma once
#include <vector>
#include "token.hpp"

enum State {
    START,
    OP,
    PAR,
    INT,
    FLOAT,
    TEXT,
    BUFFER
};

void tokenize(std::string& cur, std::vector<Token>& tokens);
