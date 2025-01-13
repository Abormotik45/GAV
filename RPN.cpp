#include "RPN.hpp"
#include "token.hpp"
#include <vector>
#include <stack>

std::vector<Token> dijkstra(std::vector<Token> tokens) {
    std::vector<Token> rpn;
    std::stack<Token> stack;

    auto stack_top_to_rpn = [&]() {rpn.push_back(stack.top()); stack.pop();};
    for (Token& token: tokens) {
        switch (token.get_type()) {
        case Token::INT_NUMBER:
        case Token::FLOAT_NUMBER:
            rpn.push_back(token);
            break;

        case Token::FUNCTION: //(or variables) 
            stack.push(token);
            break;

        case Token::SEPARATOR:
            while (stack.top().get_type() != Token::L_PARENTHESIS) {
                stack_top_to_rpn();
            }
            break;

        case Token::OPERATOR:
            while (!stack.empty() && stack.top().get_type() == Token::OPERATOR && (stack.top().get_priority() > token.get_priority() || stack.top().get_priority() == token.get_priority() && token.get_asc() == Token::RIGHT)) {
                stack_top_to_rpn();
            }
            break;

        case Token::L_PARENTHESIS:
            stack.push(token);
            break;

        case Token::R_PARENTHESIS:
            while (stack.top().get_type() != Token::L_PARENTHESIS) {
                stack_top_to_rpn();
            }
            stack.pop();
            if (stack.top().get_type() == Token::FUNCTION) 
                stack_top_to_rpn();
            break;
        }

        while (!stack.empty()) {
            stack_top_to_rpn();
        }
    }
    return rpn;
}
