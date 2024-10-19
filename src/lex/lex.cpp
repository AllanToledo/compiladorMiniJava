#include <string>
#include "lex.h"

std::string lex::token_string(int codigo) {
    switch (codigo) {
        case lex::KEYWORD:
            return "KEYWORD";
        case lex::IDENTIFIER:
            return "IDENTIFIER";
        case lex::NUM:
            return "NUM";
        case lex::ADD_OP:
            return "ADD_OP";
        case lex::MULT_OP:
            return "MULT_OP";
        case lex::REL_OP:
            return "REL_OP";
        case lex::AND_OP:
            return "AND_OP";
        case lex::OR_OP:
            return "OR_OP";
        case lex::NEG_OP:
            return "NEG_OP";
        case lex::SELF:
            return "SELF";
        default:
            return "ERROR";
    }
}