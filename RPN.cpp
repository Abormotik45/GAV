#pragma once
#include "token.hpp"
#include <vector>
#include <stack>
#include <tuple>
#include <cmath>
#include <iostream>
#include <variant>
#include "eating.cpp"
#include "sleeping.cpp"
#include "walk.cpp"
#include "hunt.cpp"

std::vector<Token> dijkstra(std::vector<Token>& tokens) {
    std::vector<Token> rpn;
    std::stack<Token> stack;

    auto stack_top_to_rpn = [&]() { rpn.push_back(stack.top()); stack.pop(); };
    for (Token& token: tokens) {
        switch (token.get_type()) {
        case Token::INT_NUMBER:
        case Token::FLOAT_NUMBER:
            rpn.push_back(token);
            break;
        
        case Token::VAR_COMM:
            rpn.push_back(token);
            break;

        case Token::FUNCTION:
            stack.push(token);
            break;

        case Token::SEPARATOR:
            while (stack.top().get_type() != Token::L_PARENTHESIS) {
                stack_top_to_rpn();
            }
            break;

        case Token::OPERATOR:
            if(!stack.empty()) {
                while(stack.top().get_type() == Token::OPERATOR && ((stack.top().get_priority() < token.get_priority())
                        || (stack.top().get_priority() == token.get_priority() && token.get_asc() == Token::LEFT)))
                {
                    stack_top_to_rpn();
                    if (stack.empty()) 
                        break;
                }
            }
            stack.push(token);
            break;

        case Token::L_PARENTHESIS:
            stack.push(token);
            break;

        case Token::R_PARENTHESIS:
        {
            // int token_count = 0;
            while (stack.top().get_type() != Token::L_PARENTHESIS) {
                // token_count++;
                stack_top_to_rpn();
            }

            stack.pop();

            /*
            if (!stack.empty() && stack.top().get_type() == Token::FUNCTION) {
                std::wstring sz_str = std::to_wstring(token_count);
                rpn.push_back(Token(sz_str, Token::FUNC_SIZE));
                stack_top_to_rpn();
            }
            */
            break;
        }
        default:
            break;
        }
    }

    while (!stack.empty()) {
        stack_top_to_rpn();
    }
    
    return rpn;
}


void calc(std::vector<Token>& rpn) {
    std::stack<std::variant<long double,std::wstring>> stack;
    auto get_one = [&]() {
        auto x = stack.top();
        stack.pop();
        return std::get<long double>(x);
    };

    auto get_one_variant = [&]() {
        auto x = stack.top();
        stack.pop();
        return x;
    };

    auto get_two = [&]() {
        auto x = get_one();
        auto y = get_one();
        return std::tuple{x, y};
    };

    for (auto& token: rpn) {
        switch (token.get_type()) {
        case Token::INT_NUMBER:
        case Token::FLOAT_NUMBER:
            stack.push(stold(token.get_str()));
            break;

        case Token::OPERATOR: 
        {
            long double res = 0;
            auto& s = token.get_str();
            switch (token.get_asc()) {
            case Token::LEFT:
                if (s == L"+") {
                    auto [y, x] = get_two();
                    res = x + y;
                }
                else if (s == L"-") {
                    auto [y, x] = get_two();
                    res = x - y;
                }
                else if (s == L"*") {
                    auto [y, x] = get_two();
                    res = x * y;
                }
                else if (s == L"/") {
                    auto [y, x] = get_two();
                    res = x / y;
                }
                else if (s == L"//") {
                    auto [y, x] = get_two();
                    res = std::floor(x / y);
                }
                //else if (s == "%") {
                    //auto [y, x] = get_two();
                    //stack.push(x % y);
                //}
                
                break;

            case Token::RIGHT:
                //if (s == "^") {
                //    auto [y, x] = get_two();
                //    res = std::pow(x, y);
                //}
                if (s == L"-") {
                    auto x = get_one();
                    res = -x;
                }

                break;
            }

            stack.push(res);
            break;
        }
        case Token::FUNCTION:
        case Token::VAR_COMM:
        {
            auto& s = token.get_str();
            //std::wcout << s << "\n" << endl;
            
            if (s == L"мяу") {
                clearScreen();
                system("aplay data/meow.wav -q &");
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            }
            else if (s == L"ам") {
                system("aplay data/eating.wav -q &");
                eating();
            }
            else if (s == L"спать") {
                system("aplay data/hrap.wav -q &");
                sleeping();
            }
            else if (s == L"гулять") {
                system("aplay data/walk.wav -q &");
                walk();
            }
            
            else if (s == L"охота") {
                hunt();
            }
            break;

        }
        default:
            break;
        }
    }
}
