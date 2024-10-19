//
// Created by Allan Toledo on 12/07/24.
//

#ifndef COMPILADORMINIJAVA_SIN_H
#define COMPILADORMINIJAVA_SIN_H

#include "../lex/lex.h"
#include "../ist/ist.h"

namespace sin {
    void reconhecer(std::vector<lex::token> &tokens, int &pos, const lex::token &match);

    void programa   (std::vector<lex::token> &tokens, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);

    void metodo         (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void params         (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions, ist::identifier &identifier);
    void mais_params    (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions, ist::identifier &identifier);
    void mais_vars      (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    int  metodo_tipo    (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void tipo           (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void cmds           (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void cmd            (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void cmd_cond       (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void pfalsa         (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void lista_arg      (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions, std::vector<uint32_t> &params);
    void mais_args      (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions, std::vector<uint32_t> &params);
    void condicao       (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void relacao        (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void expressao      (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void termo          (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void fator          (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void outros_termos  (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void chamada        (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void op_ad          (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void mais_fatores   (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
    void op_mul         (std::vector<lex::token> &tokens, int &pos, ist::identifier_tree &table, std::vector<ist::instruction> &instructions);
}

#endif //COMPILADORMINIJAVA_SIN_H
