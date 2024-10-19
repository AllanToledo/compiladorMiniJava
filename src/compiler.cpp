#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "lex/lex.h"
#include "sin/sin.h"
#include "ist/ist.h"
#include "lex/lex.yy.c"


void adicionarBibliotecaPadrao(
    std::vector<ist::instruction> &instructions,
    ist::identifier_tree &root
) {
    ist::identifier &println = ist::register_identifier(root, lex::token(lex::IDENTIFIER, "println"));
    println.address     = instructions.size() - 1;
    println.params      = { ist::DOUBLE };
    println.type        = ist::VOID;
    println.isFunction  = ist::FUNCTION;

    instructions.emplace_back(ist::IMPR, 0);
    instructions.emplace_back(ist::RTPR, 0);

    ist::identifier &read = ist::register_identifier(root, lex::token(lex::IDENTIFIER, "lerDouble"));
    read.address    = instructions.size() - 1;
    read.params     = {};
    read.type       = ist::DOUBLE;
    read.isFunction = ist::FUNCTION;

    instructions.emplace_back(ist::LEIT, 0);
    instructions.emplace_back(ist::RTPR, 0);
}

void compile(std::vector<std::string> &params) {
    std::ifstream file;
    std::string line;
    std::string output_name = "a.obj";
    std::string file_name   = params[1];

    if(params.size() >= 3)
        output_name = params[2];

    file.open(file_name);
    if(!file.is_open())
        throw std::invalid_argument("Arquivo '" + file_name + "' não pode ser aberto.\n");
    file.close();

    std::vector<lex::token> tokens = lex::get_tokens(file_name);

    ist::identifier_tree root;
    std::vector<ist::instruction> instructions;

    //Inicialização do programa.
    instructions.emplace_back(ist::ALME,   1);
    instructions.emplace_back(ist::PUSHER, 2);
    instructions.emplace_back(ist::CHPR,   0);
    instructions.emplace_back(ist::PARA,   0);

    //Definição da biblioteca padrão
    adicionarBibliotecaPadrao(instructions, root);

    //Analise dos tokens e tradução do código
    sin::programa(tokens, root, instructions);

    ist::identifier main = ist::get_identifier(root, lex::token(lex::IDENTIFIER, "main"));
    if(!main.isFunction)       throw std::invalid_argument("Método main não foi declarado.");
    if(main.type != ist::VOID) throw std::invalid_argument("Método main não foi declarado void.");
    if(!main.params.empty())   throw std::invalid_argument("Método main não pode exigir parametros.");

    instructions[2].param = main.address;

    std::ofstream out(output_name, std::ios::out);

    for(auto [code, param] : instructions) {

//        std::cout << std::setfill(' ') << std::setw(2) << i << ": "
//                  << ist::code_string(code) << ' ' << param << '\n';

        out << ist::code_string(code) << ' ' << param << '\n';
    }

    out.close();
}

int main(int argc, char * argv[]) {

    std::vector<std::string> params(argv, argv + argc);

    if(params.size() < 2) {
        std::cout << "Uso:\n\n";
        std::cout << "compiler input_file [output_file]\n\n";
        std::exit(0);
    }

    try {
        compile(params);
        std::cout << "Programa válido!\n";
    } catch (std::invalid_argument &e) {
        std::cerr << "Houver um erro no processo de compilação😵😵‍💫☠️💀:\n";
        std::cerr <<  e.what() << '\n';
    }
}
