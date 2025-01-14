#include <iostream>
#include "variables.hpp"
#include "token.hpp"
#include "tokenizer.hpp"
#include "RPN.hpp"

int main() {
    std::string filename;
    std::cin >> filename;
    freopen(filename.c_str(), "r", stdin);
    
    int cnt = 0;
    while (!std::cin.eof()) {
        cnt++;
        std::string cur;
        getline(std::cin, cur);

        std::vector<Token> tokens;
        tokenize(cur, tokens);

        auto rpn = dijkstra(tokens);

        for (auto& i: rpn) {
            std::cout << i.get_str() << "\t\t";

            std::string type;
            if (i.get_type() == Token::VAR_COMM) 
                std::cout << "VARIABLE\n";
            else if (i.get_type() == Token::FUNCTION)
                std::cout << "FUNCTION\n";
            else if (i.get_type() == Token::OPERATOR)
                std::cout << "OPERATOR\n";
            else if (i.get_type() == Token::INT_NUMBER)
                std::cout << "INT_NUMBER\n";
        }
    }
    return 0;
}
