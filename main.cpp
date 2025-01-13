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
            std::cout << i.get_str();
        }

        //count(rpn);
        std::cout << "\n";
    }
    return 0;
}
