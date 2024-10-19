#ifndef COMPILADORMINIJAVA_LEX_H
#define COMPILADORMINIJAVA_LEX_H

#include <string>

namespace lex {
    const int KEYWORD    = 0;
    const int IDENTIFIER = 1;
    const int NUM        = 2;
    const int ADD_OP     = 3;
    const int MULT_OP    = 4;
    const int REL_OP     = 5;
    const int AND_OP     = 6;
    const int OR_OP      = 7;
    const int NEG_OP     = 8;
    const int SELF       = 9;
    const int ERROR      = -1;
    typedef struct token {
        int code;
        std::string lexema;
        token(int code, const std::string &lexema) {
            this->code = code;
            this->lexema = lexema;
        }
        bool operator ==(const token& other) const {
            if(other.code   != this->code  ) return false;
            if(other.lexema != this->lexema) return false;
            return true;
        }
        bool operator !=(const token& other) const {
            return !((*this) == other);
        }
    } token;

    std::string token_string(int codigo);
    std::vector<lex::token> get_tokens(const std::string &file);
}

#endif //COMPILADORMINIJAVA_LEX_H