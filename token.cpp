#include "token.hpp"
#include <map>


Token::Token(std::string str, Type type, Associativity asc) : _type{type}, _str{str} {
    _asc = asc;
}

int Token::get_priority() {
    std::map<std::string,int> l_asc;
    l_asc["*"] = 3;
    l_asc["//"] = 3;
    l_asc["/"] = 3;
    l_asc["%"] = 3;
    l_asc["+"] = 2;
    l_asc["-"] = 2;

    l_asc["=="] = 1;
    l_asc[">"] = 1;
    l_asc[">="] = 1;
    l_asc["<"] = 1;
    l_asc["<="] = 1;

    l_asc["="] = 0;
    l_asc["*="] = 0;
    l_asc["//="] = 0;
    l_asc["%="] = 0;
    l_asc["/="] = 0;
    l_asc["-="] = 0;
    l_asc["+="] = 0;


    std::map<std::string,int> r_asc;
    r_asc["^"] = 5;
    r_asc["-"] = 4;


    switch (_asc) {
    case(LEFT):
        if (l_asc.contains(_str)) return l_asc[_str];
        break;
    case(RIGHT): 
        if (r_asc.contains(_str)) return r_asc[_str];
        break;
    }
}
