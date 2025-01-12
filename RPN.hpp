#pragma once
#include "token.hpp"
#include <vector>

std::vector<Token> dijkstra(std::vector<Token> tokens);

long double count(std::vector<Token> rpn);
