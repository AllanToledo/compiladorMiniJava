#include <vector>
#include <string>
#include "../lex/lex.h"
#include "sin.h"

void sin::reconhecer(
    std::vector<lex::token> &tokens,
    int &pos,
    const lex::token &match
) {
    if(pos >= tokens.size())
        throw std::invalid_argument("vhis, algo ta mt errado amigo.");

    switch(match.code) {
        case lex::IDENTIFIER:
            if(tokens[pos].code != match.code) {
              std::string error = "Esperado identificador. "
                                  "Porém foi encontrado '" + tokens[pos].lexema + "'.\n";
              throw std::invalid_argument(error);
            }
            break;
        case lex::REL_OP:
            if(tokens[pos].code != match.code) {
                std::string error = "Esperado operador relacional. "
                                    "Porém foi encontrado '" + tokens[pos].lexema + "'.\n";
                throw std::invalid_argument(error);
            }
            break;
        case lex::ADD_OP:
            if(tokens[pos].code != match.code) {
                std::string error = "Esperado operador de adição. "
                                    "Porém foi encontrado '" + tokens[pos].lexema + "'.\n";
                throw std::invalid_argument(error);
            }
            break;
        case lex::MULT_OP:
            if(tokens[pos].code != match.code) {
                std::string error = "Esperado operador de multiplicação. "
                                    "Porém foi encontrado '" + tokens[pos].lexema + "'.\n";
                throw std::invalid_argument(error);
            }
            break;
        case lex::NUM:
            if(tokens[pos].code != match.code) {
                std::string error = "Esperado número. "
                                    "Porém foi encontrado '" + tokens[pos].lexema + "'.\n";
                throw std::invalid_argument(error);
            }
            break;
        default:
            if(tokens[pos] != match) {
                std::string error = "Esperado '" + match.lexema + "'. "
                                    "Porém foi encontrado '" + tokens[pos].lexema + "'.\n";
                throw std::invalid_argument(error);
            }
    }

    pos++;
}


void sin::programa(
    std::vector<lex::token> &tokens, 
    ist::identifier_tree &table, 
    std::vector<ist::instruction> &instructions
) {
    int pos = 0;
    sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "public"));
    sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "class"));
    sin::reconhecer(tokens, pos, lex::token(lex::IDENTIFIER, ""));
    sin::reconhecer(tokens, pos, lex::token(lex::SELF, "{"));
    sin::metodo    (tokens, pos, table, instructions);
    sin::reconhecer(tokens, pos, lex::token(lex::SELF, "}"));
    if(pos < tokens.size())
        throw std::invalid_argument("Os caracteres excedem a definição do programa.");
}

void sin::metodo(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos] != lex::token(lex::KEYWORD, "public")) return;

    sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "public"));
    sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "static"));
    uint32_t type = sin::metodo_tipo(tokens, pos, table, instructions);

    ist::identifier &id = ist::register_identifier(table, tokens[pos]);
    id.type       = type;
    id.address    = instructions.size() - 1;
    id.isFunction = ist::FUNCTION;
    table.create_child();

    instructions.emplace_back(ist::ALME, 0);
    uint32_t alloc = instructions.size() - 1;

    sin::reconhecer(tokens, pos, lex::token(lex::IDENTIFIER, ""));
    sin::reconhecer(tokens, pos, lex::token(lex::SELF, "("));
    sin::params    (tokens, pos, *table.child, instructions, id);
    sin::reconhecer(tokens, pos, lex::token(lex::SELF, ")"));
    sin::reconhecer(tokens, pos, lex::token(lex::SELF, "{"));
    sin::cmds      (tokens, pos, *table.child, instructions);
    sin::reconhecer(tokens, pos, lex::token(lex::SELF, "}"));

    instructions[alloc].param = table.child->count;

    instructions.emplace_back(ist::RTPR, 0);

    sin::metodo    (tokens, pos, table, instructions);
}


int sin::metodo_tipo(
        std::vector<lex::token> &tokens,
        int &pos,
        ist::identifier_tree &table,
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos].lexema == "void") {
        sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "void"));
        return ist::VOID;
    } else {
        sin::tipo(tokens, pos, table, instructions);
        return ist::DOUBLE;
    }
}

void sin::tipo(
        std::vector<lex::token> &tokens,
        int &pos,
        ist::identifier_tree &table,
        std::vector<ist::instruction> &instructions
) {
    sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "double"));
}

void sin::params(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions,
        ist::identifier &identifier
) {
    if(tokens[pos] != lex::token(lex::KEYWORD, "double")) return;

    sin::tipo       (tokens, pos, table, instructions);
    ist::identifier &param_id = ist::register_identifier(table, tokens[pos]);
    param_id.address = table.address++;
    param_id.type    = ist::DOUBLE;
    identifier.params.push_back(param_id.type);
    sin::reconhecer (tokens, pos, lex::token(lex::IDENTIFIER, ""));
    sin::mais_params(tokens, pos, table, instructions, identifier);
}

void sin::mais_params(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions,
        ist::identifier &identifier
) {
    if(tokens[pos] != lex::token(lex::SELF, ",")) return;

    sin::reconhecer(tokens, pos, lex::token(lex::SELF, ","));
    sin::params    (tokens, pos, table, instructions, identifier);
}


void sin::cmds(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos].lexema == "if"
    || tokens[pos].lexema == "while"
    ) {
        sin::cmd_cond(tokens, pos, table, instructions);
        sin::cmds(tokens, pos, table, instructions);
    } else if(tokens[pos].lexema == "return"
           || tokens[pos].lexema == "double"
           || tokens[pos].code == lex::IDENTIFIER
    ) {
        sin::cmd(tokens, pos, table, instructions);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF, ";"));
        sin::cmds(tokens, pos, table, instructions);
    }

}

void sin::cmd_cond(
        std::vector<lex::token> &tokens,
        int &pos,
        ist::identifier_tree &table,
        std::vector<ist::instruction> &instructions
){
    if(tokens[pos].lexema == "if") {
        sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "if"));
        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "("));
        sin::condicao  (tokens, pos, table, instructions);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    ")"));

        instructions.emplace_back(ist::DSVF, 0);
        uint64_t pos_jump_to_else = instructions.size() - 1;

        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "{"));

        table.create_child();

        sin::cmds      (tokens, pos, *table.child, instructions);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "}"));

        instructions.emplace_back(ist::DSVI, 0);
        uint64_t pos_jump_to_end = instructions.size() - 1;

        instructions[pos_jump_to_else].param = instructions.size() - 1;

        sin::pfalsa    (tokens, pos, table, instructions);

        instructions[pos_jump_to_end].param = instructions.size() - 1;

    } else if(tokens[pos].lexema == "while") {

        uint64_t top_of_while = instructions.size() - 1;

        sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "while"));
        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "("));
        sin::condicao  (tokens, pos, table, instructions);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    ")"));

        table.create_child();

        instructions.emplace_back(ist::DSVF, 0);
        uint64_t pos_jump_to_end = instructions.size() - 1;

        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "{"));
        sin::cmds      (tokens, pos, *table.child, instructions);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "}"));

        instructions.emplace_back(ist::DSVI, top_of_while);

        instructions[pos_jump_to_end].param = instructions.size() - 1;

    }
}

void sin::cmd(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos].code == lex::IDENTIFIER) {
        ist::identifier id = ist::get_identifier(table, tokens[pos]);
        sin::reconhecer(tokens, pos, lex::token(lex::IDENTIFIER, ""));
        if(tokens[pos] == lex::token(lex::SELF, "=")) {
            sin::reconhecer(tokens, pos, lex::token(lex::SELF, "="));
            sin::expressao (tokens, pos, table, instructions);
            instructions.emplace_back(ist::ARMZ, id.address);
        } else if(tokens[pos] == lex::token(lex::SELF, "(")) {

            instructions.emplace_back(ist::ALME,   1);

            instructions.emplace_back(ist::PUSHER, 0);
            uint32_t call = instructions.size() - 1;

            sin::reconhecer(tokens, pos, lex::token(lex::SELF, "("));
            std::vector<uint32_t> params;
            sin::lista_arg (tokens, pos, table, instructions, params);
            sin::reconhecer(tokens, pos, lex::token(lex::SELF, ")"));

            if(params != id.params)
                throw std::invalid_argument("Parametros inválidos.");

            instructions.emplace_back(ist::CHPR, id.address);
            instructions[call].param = instructions.size() - 1;
            instructions.emplace_back(ist::DESM,          1);

        } else {
            throw std::invalid_argument("Comando inesperado em: '" + tokens[pos].lexema + "'\n");
        }
    } else if(tokens[pos].lexema == "double") {
        sin::tipo(tokens, pos, table, instructions);
        lex::token variable = tokens[pos];
        sin::reconhecer(tokens, pos, lex::token(lex::IDENTIFIER, ""));
        ist::identifier &id = ist::register_identifier(table, variable);
        id.address = table.address++; table.count++;
        id.type = ist::DOUBLE;
        sin::mais_vars (tokens, pos, table, instructions);
    } else if(tokens[pos].lexema == "return") {
        sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "return"));
        sin::expressao(tokens, pos, table, instructions);
        instructions.emplace_back(ist::RTPR, 0);
    } else {
        throw std::invalid_argument("Comando inválido: '" + tokens[pos].lexema + "'.\n");
    }
}

void sin::mais_vars(
        std::vector<lex::token> &tokens,
        int &pos,
        ist::identifier_tree &table,
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos] != lex::token(lex::SELF, ",")) return;

    sin::reconhecer(tokens, pos, lex::token(lex::SELF, ","));
    lex::token variable = tokens[pos];
    sin::reconhecer(tokens, pos, lex::token(lex::IDENTIFIER, ""));
    ist::identifier &id = ist::register_identifier(table, variable);
    id.address = table.address++;
    table.count++;
    id.type = ist::DOUBLE;
    sin::mais_vars (tokens, pos, table, instructions);
}

void sin::pfalsa(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos] != lex::token(lex::KEYWORD, "else")) return;

    sin::reconhecer(tokens, pos, lex::token(lex::KEYWORD, "else"));
    sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "{"));
    sin::cmds      (tokens, pos, table, instructions);
    sin::reconhecer(tokens, pos, lex::token(lex::SELF,    "}"));
}

void sin::lista_arg(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions,
        std::vector<uint32_t> &params
) {
    if(tokens[pos].lexema == ")") return;

    sin::expressao(tokens, pos, table, instructions);
    params.push_back(ist::DOUBLE);
    sin::mais_args(tokens, pos, table, instructions, params);
}

void sin::mais_args(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions,
        std::vector<uint32_t> &params
) {
    if(tokens[pos] != lex::token(lex::SELF, ",")) return;

    sin::reconhecer(tokens, pos, lex::token(lex::SELF, ","));
    sin::expressao(tokens, pos, table, instructions);
    params.push_back(ist::DOUBLE);
    sin::mais_args(tokens, pos, table, instructions, params);
}

void sin::condicao(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    sin::expressao(tokens, pos, table, instructions);
    lex::token operation = tokens[pos];
    sin::relacao  (tokens, pos, table, instructions);
    sin::expressao(tokens, pos, table, instructions);

    if(operation.lexema == ">") {
        instructions.emplace_back(ist::CPMA, 0);
    } else if(operation.lexema == "<") {
        instructions.emplace_back(ist::CPME, 0);
    } else if(operation.lexema == ">=") {
        instructions.emplace_back(ist::CMAI, 0);
    } else if(operation.lexema == "<=") {
        instructions.emplace_back(ist::CPMI, 0);
    } else if(operation.lexema == "==") {
        instructions.emplace_back(ist::CPIG, 0);
    } else if(operation.lexema == "!=") {
        instructions.emplace_back(ist::CDES, 0);
    }
}

void sin::relacao(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    reconhecer(tokens, pos, lex::token(lex::REL_OP, ""));
}

void sin::expressao(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    sin::termo(tokens, pos, table, instructions);
    sin::outros_termos(tokens, pos, table, instructions);
}

void sin::termo(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    sin::fator(tokens, pos, table, instructions);
    sin::mais_fatores(tokens, pos, table, instructions);
}

void sin::fator(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos].code == lex::IDENTIFIER) {
        sin::chamada   (tokens, pos, table, instructions);
    } else if(tokens[pos].code == lex::NUM) {
        lex::token literal = tokens[pos];
        sin::reconhecer(tokens, pos, lex::token(lex::NUM, ""));
        instructions.emplace_back(ist::CRCT, std::stod(literal.lexema));
    } else if(tokens[pos] == lex::token(lex::SELF, "(")) {
        sin::reconhecer(tokens, pos, lex::token(lex::SELF, "("));
        sin::expressao (tokens, pos, table, instructions);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF, ")"));
    } else if(tokens[pos] == lex::token(lex::ADD_OP, "-")) {
        sin::reconhecer(tokens, pos, lex::token(lex::ADD_OP, "-"));
        sin::fator     (tokens, pos, table, instructions);
        instructions.emplace_back(ist::INVE, 0);
    } else {
        throw std::invalid_argument("Fator inesperado: '" + tokens[pos].lexema + "'.\n");
    }
}

void sin::chamada(
        std::vector<lex::token> &tokens,
        int &pos,
        ist::identifier_tree &table,
        std::vector<ist::instruction> &instructions
) {
    lex::token id_token = tokens[pos];
    ist::identifier id = ist::get_identifier(table, id_token);
    sin::reconhecer(tokens, pos, lex::token(lex::IDENTIFIER, ""));
    if(tokens[pos].lexema == "(") {
        if(id.isFunction != ist::FUNCTION)
            throw std::invalid_argument(id_token.lexema + " não é um método.");

        if(id.type == ist::VOID)
            throw std::invalid_argument(id_token.lexema + " não possui retorno.");

        instructions.emplace_back(ist::ALME,   1);
        instructions.emplace_back(ist::PUSHER, 0);
        uint32_t call = instructions.size() - 1;

        sin::reconhecer(tokens, pos, lex::token(lex::SELF, "("));
        std::vector<uint32_t> params;
        sin::lista_arg (tokens, pos, table, instructions, params);
        sin::reconhecer(tokens, pos, lex::token(lex::SELF, ")"));

        if(params != id.params)
            throw std::invalid_argument("Parametros inválidos.");

        instructions.emplace_back(ist::CHPR, id.address);
        instructions[call].param = instructions.size() - 1;

    } else {
        instructions.emplace_back(ist::CRVL, id.address);
    }
}

void sin::outros_termos(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos].code != lex::ADD_OP) return;

    lex::token operation = tokens[pos];
    sin::op_ad(tokens, pos, table, instructions);
    sin::termo(tokens, pos, table, instructions);
    sin::outros_termos(tokens, pos, table, instructions);

    if(operation.lexema == "+") {
        instructions.emplace_back(ist::SOMA, 0);
    } else {
        instructions.emplace_back(ist::SUBT, 0);
    }
}

void sin::op_ad(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    sin::reconhecer(tokens, pos, lex::token(lex::ADD_OP, ""));
}

void sin::mais_fatores(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    if(tokens[pos].code != lex::MULT_OP) return;

    lex::token operation = tokens[pos];

    sin::op_mul      (tokens, pos, table, instructions);
    sin::fator       (tokens, pos, table, instructions);
    sin::mais_fatores(tokens, pos, table, instructions);

    if(operation.lexema == "*") {
        instructions.emplace_back(ist::MULT, 0);
    } else {
        instructions.emplace_back(ist::DIVI, 0);
    }
}

void sin::op_mul(
        std::vector<lex::token> &tokens, 
        int &pos, 
        ist::identifier_tree &table, 
        std::vector<ist::instruction> &instructions
) {
    sin::reconhecer(tokens, pos, lex::token(lex::MULT_OP, ""));
}






