#include "token.hpp"
#include <map>
#include <set>

Token::Token(std::string str, Type type, Associativity asc) : _type{type}, _str{str} {
    _asc = asc;
}

int Token::get_priority() {
    std::map<std::string,int> l_asc {
        {"++", 2},
        {"--", 2},
        {"*", 4},
        {"/", 4},
        {"//", 4},
        {"%", 4},
        {"+", 5},
        {"-", 5},
        {"<<", 6},
        {">>", 6},
        {"<", 7},
        {"<=", 7},
        {">", 7},
        {">=", 7},
        {"==", 8},
        {"!=", 8},
        {"&&", 9},
        {"||", 10}
    };

    std::map<std::string,int> r_asc {
        {"!", 2},
        {"++", 3},
        {"--", 3},
        {"^", 3},
        {"-", 5},

        {"=", 12},
        {"*=", 12},
        {"/=", 12},
        {"//=", 12},
        {"+=", 12},
        {"-=", 12},
        {"^=", 12},
        {"<<=", 12},
        {">>=", 12}
    };


    switch (_asc) {
    case(LEFT):
        if (l_asc.contains(_str)) return l_asc[_str];
        break;
    case(RIGHT): 
        if (r_asc.contains(_str)) return r_asc[_str];
        break;
    default:
        break;
    }
}

Token::Associativity get_asc(std::string s) {
    std::map<std::string, Token::Associativity> map {
        {"*", Token::LEFT},
        {"/", Token::LEFT},
        {"//", Token::LEFT},
        {"%", Token::LEFT},
        {"+", Token::LEFT},
        {"-", Token::LEFT},
        {"<<", Token::LEFT},
        {">>", Token::LEFT},
        {"<", Token::LEFT},
        {"<=", Token::LEFT},
        {">", Token::LEFT},
        {">=", Token::LEFT},
        {"==", Token::LEFT},
        {"!=", Token::LEFT},
        {"&&", Token::LEFT},
        {"||", Token::LEFT},

        {"!", Token::RIGHT},
        {"++", Token::RIGHT},
        {"--", Token::RIGHT},
        {"^", Token::RIGHT},
        {"=", Token::RIGHT},
        {"*=", Token::RIGHT},
        {"/=", Token::RIGHT},
        {"//=", Token::RIGHT},
        {"+=", Token::RIGHT},
        {"-=", Token::RIGHT},
        {"^=", Token::RIGHT},
        {"<<=", Token::RIGHT},
        {">>=", Token::RIGHT}
    };
    return map[s];
}
