#include "token.hpp"
#include <map>
#include <set>

Token::Token(std::wstring str, Type type, Associativity asc) : _type{type}, _str{str} {
    _asc = asc;
}

int Token::get_priority() {
    std::map<std::wstring,int> l_asc {
        {L"++", 2},
        {L"--", 2},
        {L"*", 4},
        {L"/", 4},
        {L"//", 4},
        {L"%", 4},
        {L"+", 5},
        {L"-", 5},
        {L"<<", 6},
        {L">>", 6},
        {L"<", 7},
        {L"<=", 7},
        {L">", 7},
        {L">=", 7},
        {L"==", 8},
        {L"!=", 8},
        {L"&&", 9},
        {L"||", 10}
    };

    std::map<std::wstring,int> r_asc {
        {L"!", 2},
        {L"++", 3},
        {L"--", 3},
        {L"^", 3},
        {L"-", 5},

        {L"=", 12},
        {L"*=", 12},
        {L"/=", 12},
        {L"//=", 12},
        {L"+=", 12},
        {L"-=", 12},
        {L"^=", 12},
        {L"<<=", 12},
        {L">>=", 12}
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

Token::Associativity get_asc(std::wstring s) {
    std::map<std::wstring, Token::Associativity> map {
        {L"*", Token::LEFT},
        {L"/", Token::LEFT},
        {L"//", Token::LEFT},
        {L"%", Token::LEFT},
        {L"+", Token::LEFT},
        {L"-", Token::LEFT},
        {L"<<", Token::LEFT},
        {L">>", Token::LEFT},
        {L"<", Token::LEFT},
        {L"<=", Token::LEFT},
        {L">", Token::LEFT},
        {L">=", Token::LEFT},
        {L"==", Token::LEFT},
        {L"!=", Token::LEFT},
        {L"&&", Token::LEFT},
        {L"||", Token::LEFT},

        {L"!", Token::RIGHT},
        {L"++", Token::RIGHT},
        {L"--", Token::RIGHT},
        {L"^", Token::RIGHT},
        {L"=", Token::RIGHT},
        {L"*=", Token::RIGHT},
        {L"/=", Token::RIGHT},
        {L"//=", Token::RIGHT},
        {L"+=", Token::RIGHT},
        {L"-=", Token::RIGHT},
        {L"^=", Token::RIGHT},
        {L"<<=", Token::RIGHT},
        {L">>=", Token::RIGHT}
    };
    return map[s];
}
