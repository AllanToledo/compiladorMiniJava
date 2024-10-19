//
// Created by Allan Toledo on 17/07/24.
//

#ifndef COMPILADORMINIJAVA_IST_H
#define COMPILADORMINIJAVA_IST_H

#include "../lex/lex.h"
#include <string>
#include <map>

namespace ist {

    const uint32_t INPP   = -1;
    const uint32_t PARA   =  0;
    const uint32_t CRVL   =  1;
    const uint32_t CRCT   =  2;
    const uint32_t ARMZ   =  3;
    const uint32_t POP    =  4;
    const uint32_t SOMA   =  5;
    const uint32_t SUBT   =  6;
    const uint32_t MULT   =  7;
    const uint32_t DIVI   =  8;
    const uint32_t IMPR   =  9;
    const uint32_t LEIT   = 10;
    const uint32_t DSVI   = 11;
    const uint32_t ALME   = 12;
    const uint32_t CPIG   = 13;
    const uint32_t CDES   = 14;
    const uint32_t CPME   = 15;
    const uint32_t CPMA   = 16;
    const uint32_t CPMI   = 17;
    const uint32_t CMAI   = 18;
    const uint32_t DSVF   = 19;
    const uint32_t INVE   = 20;
    const uint32_t CALL   = 21;
    const uint32_t RTPR   = 22;
    const uint32_t CONJ   = 23;
    const uint32_t DISJ   = 24;
    const uint32_t NEGA   = 25;
    const uint32_t PARAM  = 26;
    const uint32_t PUSHER = 27;
    const uint32_t CHPR   = 28;
    const uint32_t DESM   = 29;

    struct instruction {
        uint32_t code;
        double   param;
        instruction(uint32_t code, double param) {
            this->code  = code;
            this->param = param;
        }
        instruction() {}
    };

    const char VARIABLE = 0;
    const char FUNCTION = 1;

    const char VOID   = 0;
    const char DOUBLE = 1;

    typedef struct identifier {
        uint32_t type;
        uint32_t address;
        uint32_t isFunction;
        std::vector<uint32_t> params;

        identifier(uint32_t type,
                   uint32_t address,
                   uint64_t isFunction
       ) {
            this->type       = type;
            this->address    = address;
            this->isFunction = isFunction;
        }

        identifier() {
            this->type = this->address = -1;
            this->isFunction = 0;
        }

    } identifier;

    typedef struct identifier_tree {
        identifier_tree *parent = NULL;
        identifier_tree *child  = NULL;
        std::map<std::string, identifier> table;
        uint32_t count   = 0;
        uint32_t address = 0;
        void create_child() {
            child = new identifier_tree;
            child->address = this->address;
            child->parent = this;
        }
    } identifier_tree;


    identifier &register_identifier(ist::identifier_tree &tree,  const lex::token &variable);
    identifier &get_identifier     (ist::identifier_tree &table, const lex::token &variable);

    std::string code_string(uint32_t     code);
    uint32_t    code_parse (std::string &code);

}

#endif //COMPILADORMINIJAVA_IST_H
