#include <iostream>
#include "variables.hpp"
#include "token.hpp"
#include "tokenizer.hpp"

int main() {
    std::string filename;
    std::cin >> filename;
    freopen(filename.c_str(), "r", stdin);
    
    int cnt = 0;
    while (!std::cin.eof()) {
        std::cout << "\n";

        cnt++;
        std::string cur;
        getline(std::cin, cur);

        std::vector<Token> tokens;
        tokenize(cur, tokens);

        for (auto& i: tokens) {
            std::string type, asc;
            switch (i.get_type()) {
            case Token::OPERATOR:
                type = "OPERATOR";
                break;
            case Token::L_PARENTHESIS:
                type = "L_PARENTHESIS";
                break;
            case Token::R_PARENTHESIS:
                type = "R_PARENTHESIS";
                break;
            case Token::INT_NUMBER:
                type = "INT_NUMBER";
                break;
            case Token::FLOAT_NUMBER:
                type = "FLOAT_NUMBER";
                break;
            case Token::FUNCTION:
                type = "FUNCTION / VAR";
                break;
            case Token::SEPARATOR:
                type = "OPERATOR";
                break;
            }

            switch(i.get_asc()) {
            case Token::NONE:
                asc = "NONE";
                break;
            case Token::RIGHT:
                asc = "RIGHT";
                break;
            case Token::LEFT:
                asc = "LEFT";
                break;
            }
            std::cout << i.get_str() << "\t\t" << type << "\t\t" << asc << "\n";
        }
    }
    return 0;
}
