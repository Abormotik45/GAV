#include "RPN.hpp"
#include "token.hpp"
#include <vector>
#include <stack>

std::vector<Token> dijkstra(std::vector<Token> tokens) {
    std::vector<Token> rpn;
    std::stack<Token> stack;

    for (Token& token: tokens) {
        switch (token.get_type()) {
        case Token::INT_NUMBER:
        case Token::FLOAT_NUMBER:
            rpn.push_back(token);
            break;
        case Token::FUNCTION:
        case Token::L_PARENTHESIS:
            stack.push(token);
            break;
        }
    }
    return rpn;
}
