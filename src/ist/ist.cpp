#include <string>
#include "ist.h"

ist::identifier &ist::register_identifier(ist::identifier_tree &tree, const lex::token &variable) {
    if(tree.table.find(variable.lexema) != tree.table.end())
        throw std::invalid_argument("Identificador '" + variable.lexema + "' já declarado.\n");
    return tree.table[variable.lexema] = ist::identifier();
}

ist::identifier &ist::get_identifier(ist::identifier_tree  &tree, const lex::token &variable) {
    auto iterator = tree.table.find(variable.lexema);
    if(iterator == tree.table.end()) {
        if(tree.parent == nullptr) {
            throw std::invalid_argument("Identificador '" + variable.lexema + "' não foi declarado.\n");
        } else {
            return ist::get_identifier(*tree.parent, variable);
        }
    }
    return iterator->second;
}

std::string ist::code_string(uint32_t code) {
    switch (code) {
        case ist::INPP:   return "INPP";
        case ist::PARA:   return "PARA";
        case ist::CRVL:   return "CRVL";
        case ist::CRCT:   return "CRCT";
        case ist::ARMZ:   return "ARMZ";
        case ist::POP:    return "POP";
        case ist::SOMA:   return "SOMA";
        case ist::SUBT:   return "SUBT";
        case ist::MULT:   return "MULT";
        case ist::DIVI:   return "DIVI";
        case ist::IMPR:   return "IMPR";
        case ist::LEIT:   return "LEIT";
        case ist::DSVI:   return "DSVI";
        case ist::ALME:   return "ALME";
        case ist::CPIG:   return "CPIG";
        case ist::CDES:   return "CDES";
        case ist::CPME:   return "CPME";
        case ist::CPMA:   return "CPMA";
        case ist::CPMI:   return "CPMI";
        case ist::CMAI:   return "CMAI";
        case ist::DSVF:   return "DSVF";
        case ist::INVE:   return "INVE";
        case ist::CALL:   return "CALL";
        case ist::RTPR:   return "RTPR";
        case ist::CONJ:   return "CONJ";
        case ist::DISJ:   return "DISJ";
        case ist::NEGA:   return "NEGA";
        case ist::PARAM:  return "PARAM";
        case ist::PUSHER: return "PUSHER";
        case ist::CHPR:   return "CHPR";
        case ist::DESM:   return "DESM";
        default:
            return std::to_string(code);
    }
}

uint32_t ist::code_parse(std::string &code) {
    if(code == "INPP")   return ist::INPP;
    if(code == "PARA")   return ist::PARA;
    if(code == "CRVL")   return ist::CRVL;
    if(code == "CRCT")   return ist::CRCT;
    if(code == "ARMZ")   return ist::ARMZ;
    if(code == "POP")    return ist::POP;
    if(code == "SOMA")   return ist::SOMA;
    if(code == "SUBT")   return ist::SUBT;
    if(code == "MULT")   return ist::MULT;
    if(code == "DIVI")   return ist::DIVI;
    if(code == "IMPR")   return ist::IMPR;
    if(code == "LEIT")   return ist::LEIT;
    if(code == "DSVI")   return ist::DSVI;
    if(code == "ALME")   return ist::ALME;
    if(code == "CPIG")   return ist::CPIG;
    if(code == "CDES")   return ist::CDES;
    if(code == "CPME")   return ist::CPME;
    if(code == "CPMA")   return ist::CPMA;
    if(code == "CPMI")   return ist::CPMI;
    if(code == "CMAI")   return ist::CMAI;
    if(code == "DSVF")   return ist::DSVF;
    if(code == "INVE")   return ist::INVE;
    if(code == "CALL")   return ist::CALL;
    if(code == "RTPR")   return ist::RTPR;
    if(code == "CONJ")   return ist::CONJ;
    if(code == "DISJ")   return ist::DISJ;
    if(code == "NEGA")   return ist::NEGA;
    if(code == "PARAM")  return ist::PARAM;
    if(code == "PUSHER") return ist::PUSHER;
    if(code == "CHPR")   return ist::CHPR;
    if(code == "DESM")   return ist::DESM;
    return 0;
}