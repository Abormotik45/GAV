#include "tokenizer.hpp"
#include <set>
#include <cctype>

void tokenize (std::string& cur, std::vector<Token>& tokens) {
    State state = START;
    
    std::string valid_op_chars = "+-=^*/%<>!&|";
    std::set<std::string> valid_ops {
        "++", "--",
        "+", "-",
        "+=", "-=",
        "^", "*", "/", "//", "%",
        "^=", "*=", "/=", "//=", "%=",
        "<<", ">>", "<<=", ">>=",
        "<", "<=", ">", ">+", "==", "!=",
        "&&", "||", "=", "!"
    };

    std::string buffer;
    Token::Type buffer_type = Token::DEFAULT;

    bool is_num, is_letter, is_op, is_point, is_sep, is_par, is_Lpar, is_Rpar;
    
    for (auto s: cur) {
        // тип символа
        is_num = std::isdigit(s);
        is_letter = std::isalpha(s);
        is_op = (valid_op_chars.find(s) != valid_op_chars.npos);
        is_point = (s == '.');
        is_sep = (s == ',');
        is_Lpar = (s == '(');
        is_Rpar = (s == ')');
        is_par = (is_Lpar || is_Rpar);


        if (s == ' ') continue;
        if (s == '#') break;

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
            else if (is_num || is_letter || is_Lpar)
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
            else if (is_op || is_par || is_sep) 
                state = BUFFER;
            // DO else error
            break;
        case (FLOAT):
            buffer_type = Token::FLOAT_NUMBER;
            if (is_num)
                state = FLOAT;
            else if (is_op || is_par || is_sep) 
                state = BUFFER; 
            // DO else error
            break;
        case (TEXT):
            buffer_type = Token::VAR_COMM;
            if (is_letter || is_num) 
                state = TEXT;
            else if (is_par || is_op)
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
                if (is_Lpar && !tokens.empty() && tokens.back().get_type() == Token::VAR_COMM) {
                    auto del_token = tokens.back();
                    del_token.set_type(Token::FUNCTION);
                    tokens.pop_back();
                    tokens.push_back(del_token);
                }
                tokens.emplace_back(std::string{s}, (is_Rpar ? Token::R_PARENTHESIS : Token::L_PARENTHESIS));
            }
            else if (is_sep) {
                tokens.emplace_back(std::string{s}, Token::SEPARATOR);
            }
        };

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
                if (valid_ops.find(buffer) != valid_ops.end()) {
                    if (buffer == "++" || buffer == "--") {
                        if (!tokens.empty() && (tokens.back().get_type() == Token::INT_NUMBER ||
                        tokens.back().get_type() == Token::VAR_COMM)) 
                            tokens.push_back(Token(buffer, Token::OPERATOR, Token::RIGHT));
                        else 
                            tokens.push_back(Token(buffer, Token::OPERATOR, Token::LEFT));
                    }
                    else {
                        if (buffer == "-") {
                            if(tokens.size() == 0 || tokens.back().get_type() == Token::L_PARENTHESIS)
                                tokens.emplace_back(buffer, Token::OPERATOR, Token::RIGHT);
                            else
                                tokens.emplace_back(buffer, Token::OPERATOR, Token::LEFT);
                        }
                        else tokens.push_back(Token(buffer, Token::OPERATOR, get_asc(buffer)));
                    }
                }
                // else Error!!!
            }
            else if (buffer_type != Token::DEFAULT) {
                tokens.emplace_back(buffer, buffer_type);
            }
            buffer.clear();
            buffer_type = Token::DEFAULT;
            ans_par_sep();


            if (is_num) { 
                state = INT;
                buffer_type = Token::INT_NUMBER;
                buffer.push_back(s);
            }
            else if (is_letter) { 
                state = TEXT;
                buffer_type = Token::VAR_COMM;
                buffer.push_back(s);
            }
            else if (is_op) { 
                state = OP;
                buffer_type = Token::OPERATOR;
                buffer.push_back(s);
            }

            break;
        }
    }
    if (!buffer.empty()) {
        if (buffer_type == Token::OPERATOR) {
            if (valid_ops.find(buffer) != valid_ops.end()) {
                if (buffer == "++" || buffer == "--") {
                    if (!tokens.empty() && (tokens.back().get_type() == Token::INT_NUMBER ||
                    tokens.back().get_type() == Token::VAR_COMM)) 
                        tokens.push_back(Token(buffer, Token::OPERATOR, Token::RIGHT));
                    else 
                        tokens.push_back(Token(buffer, Token::OPERATOR, Token::LEFT));
                }
                else {
                    tokens.push_back(Token(buffer, Token::OPERATOR, get_asc(buffer)));
                }
            }
            // else Error!!!
        }
        
        else {
            tokens.emplace_back(buffer, buffer_type);
        }
        buffer.clear();
    }
}
