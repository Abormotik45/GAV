#pragma once
#include <string>

class Token {
public:
    enum Type {
        OPERATOR,
        INT_NUMBER,
        FLOAT_NUMBER,
        FUNCTION, // or VARIABLE
        SEPARATOR,
        L_PARENTHESIS,
        R_PARENTHESIS
    };
 
    enum Associativity {
        NONE, // if Type != OPERATOR
        LEFT,
        RIGHT
    };
    Token(std::string str, Type type, Associativity asc = NONE);

    std::string& get_str() {return _str;}
    Type& get_type() {return _type;}
    Associativity& get_asc() {return _asc;}
    int get_priority();

private:
    std::string _str;
    Type _type;
    Associativity _asc;
};
