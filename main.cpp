#include <iostream>
#include "token.cpp"
#include "tokenizer.cpp"
#include "RPN.cpp"


int main() {
    setlocale(0, "");
    std::string filename;
    std::cin >> filename;
    freopen(filename.c_str(), "r", stdin);
    
    int cnt = 0;
    while (!std::wcin.eof()) {
        cnt++;
        std::wstring cur;
        getline(std::wcin, cur);
        if (cur.empty())
            continue;

        std::vector<Token> tokens;
        tokenize(cur, tokens);

        auto rpn = dijkstra(tokens);

        calc(rpn);
    }
    return 0;
}
