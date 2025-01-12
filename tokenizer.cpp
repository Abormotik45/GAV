#include "tokenizer.hpp"
#include <set>
#include <cctype>

void tokenize (std::string& cur, std::vector<Token>& tokens) {
    State state = START;
    
    std::string valid_ops = "+-*/%^=><";
    std::string buffer;
    Token::Type buffer_type = Token::INT_NUMBER;

    bool is_num, is_letter, is_op, is_point, is_sep, is_par, is_Lpar, is_Rpar, is_space;
    
    for (auto s: cur) {
        // тип символа
        is_num = std::isdigit(s);
        is_letter = std::isalpha(s);
        is_op = (valid_ops.find(s) != valid_ops.npos);
        is_point = (s == '.');
        is_sep = (s == ',');
        is_Lpar = (s == '(');
        is_Rpar = (s == ')');
        is_par = (is_Lpar || is_Rpar);
        is_space = (s == ' ');


        if (is_space) continue;

        // смена состояния в автомате
        switch (state) {
        case (START):
            if (is_op) 
                state = OP;
            else if (is_par) 
                state = PAR;
            else if (is_num)
                state = INT;
            else if (is_letter) 
                state = TEXT;
            // DO else error
            break;
        case (OP):
            buffer_type = Token::OPERATOR;
            if (is_op)
                state = OP;
            else if (is_num || is_letter || is_Lpar || is_space)
                state = BUFFER;
            // DO else error
            break;
        case (PAR):
            if (is_op) 
                state = OP;
            else if (is_num)
                state = INT;
            else if (is_letter)
                state = TEXT;
            else if (is_par || is_sep)
                state = PAR;
            // DO else error
            break;
        case (INT):
            buffer_type = Token::INT_NUMBER;
            if (is_num) 
                state = INT;
            else if (is_point)
                state = FLOAT;
            else if (is_op || is_par || is_sep || is_space) 
                state = BUFFER;
            // DO else error
            break;
        case (FLOAT):
            buffer_type = Token::FLOAT_NUMBER;
            if (is_num)
                state = FLOAT;
            else if (is_op || is_par || is_sep || is_space) 
                state = BUFFER; 
            // DO else error
            break;     
        case (TEXT):
            buffer_type = Token::FUNCTION;
            if (is_letter || is_num) 
                state = TEXT;
            else if (is_par || is_op || is_space)
                state = BUFFER;
            // DO else error 
            break;
        case (BUFFER):
            if (is_op)
                state = OP;
            else if (is_par)
                state = PAR;
            else if (is_num) 
                state = INT;
            else if (is_letter)
                state = TEXT;
            // DO else error
            break;
        default:
            break;
        }
        

        auto ans_par_sep = [&]() {
            if (is_par) {
                tokens.emplace_back(std::string{s}, (is_Rpar ? Token::R_PARENTHESIS : Token::L_PARENTHESIS));
            }
            else if (is_sep) {
                tokens.emplace_back(std::string{s}, Token::SEPARATOR);
            }
        };

        // DOOOOOOO THIS
        // обработка
        switch (state) {
        case (PAR):
            ans_par_sep();
            break;
        case (OP): case (INT): case (FLOAT): case (TEXT):
            buffer.push_back(s);
            break;
        case (BUFFER):
            if (buffer_type == Token::OPERATOR) {
                if (buffer.back() ==  '^' || tokens.size() == 0 || tokens.back().get_type() == Token::L_PARENTHESIS)
                    tokens.emplace_back(buffer, Token::OPERATOR, Token::RIGHT);
                else
                    tokens.emplace_back(buffer, Token::OPERATOR, Token::LEFT);
            }
            else {
                tokens.emplace_back(buffer, buffer_type);
            }
            buffer.clear();
            ans_par_sep();

            if (is_num) { 
                state = INT;
                buffer.push_back(s);
            }
            else if (is_letter) { 
                state = TEXT;
                buffer.push_back(s);
            }
            else if (is_op) { 
                state = OP;
                buffer.push_back(s);
            }

            break;
        }
    }
    if (!buffer.empty()) {
        if (buffer_type == Token::OPERATOR) {
            if (tokens.size() == 0 || tokens.back().get_type() == Token::L_PARENTHESIS)
                tokens.emplace_back(buffer, Token::OPERATOR, Token::RIGHT);
            else
                tokens.emplace_back(buffer, Token::OPERATOR, Token::LEFT);
        }
        else {
            tokens.emplace_back(buffer, buffer_type);
        }
        buffer.clear();
    }
}
