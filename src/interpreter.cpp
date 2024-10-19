#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "ist/ist.h"

double  compare  (double left, double right, uint32_t type);
double  logic_op (double left, double right, uint32_t type);
double  operation(double left, double right, uint32_t type);

std::vector<std::string> split(std::string s, char delimiter) {
    std::string aux;
    std::vector<std::string> result;
    for(char c: s) {
        if(c == delimiter) {
            result.push_back(aux);
            aux.clear();
        } else {
            aux.push_back(c);
        }
    }
    result.push_back(aux);
    return std::move(result);
}

int main(int argc, char * argv[])  {

    std::vector<std::string> params(argv, argv + argc);

    if(params.size() < 2) {
        std::cout << "Uso:\n\n";
        std::cout << "interpreter input_file\n\n";
        std::exit(0);
    }

    std::string file_name = params[1];

    std::vector<ist::instruction> codigo;
    std::vector<double>           dados(1 << 15);
    std::vector<uint32_t>         base(1 << 15);

    uint32_t i = 0;
    uint32_t s = 0;
    uint32_t b = 0;
    uint32_t c = 0;

    std::ifstream input(file_name, std::ios::in);

    if(!input.is_open()) {
        std::cerr << "Não foi possível abrir arquivo '" + file_name + "'.\n";
        exit(0);
    }
    std::string line;
    while(getline(input, line)) {
        std::vector<std::string> instruction = split(line, ' ');
        codigo.emplace_back();
        codigo.back().code  = ist::code_parse(instruction[0]);
        codigo.back().param = std::stoi(instruction[1]);
    }

    input.close();

    base[0] = i;
    base[1] = s;
    base[2] = c;

    b = 3;
    c = b;

    while(codigo[i].code) {
        auto [code, param] = codigo[i];
//        std::cout << std::setfill(' ') << std::setw(2) << i
//         << ": " << ist::code_string(code) << ' ' << param << '\n';
        uint32_t offset = base[c - 2] + 1;
        switch (code) {
            case ist::CRCT: {
                dados[++s] = codigo[i].param;
            }
            break;
            case ist::CRVL: {
                dados[++s] = dados[int(param) + offset];
            }
            break;
            case ist::SOMA:
            case ist::SUBT:
            case ist::MULT:
            case ist::DIVI: {
                double right = dados[s--];
                double left  = dados[s];
                dados[s] = (operation(left, right, code));
            }
            break;
            case ist::INVE: {
                dados[s] = -dados[s];
            }
            break;
            case ist::DISJ:
            case ist::CONJ:{
                double right = dados[s--];
                double left  = dados[s];
                dados[s] = (logic_op(left, right, code));
            }
            break;
            case ist::NEGA: {
                dados[s] = !int(dados[s]);
            }
            break;
            case ist::CPIG:
            case ist::CPME:
            case ist::CPMI:
            case ist::CPMA:
            case ist::CMAI:{
                double right = dados[s--];
                double left  = dados[s];
                dados[s] = (compare(left, right, code));
            }
            break;
            case ist::ARMZ: {
                dados[int(param) + offset] = dados[s--];
            }
            break;
            case ist::DSVI:
                i = int(param);
            break;
            case ist::DSVF: {
                i = dados[s--] == 0 ? int(param) : i;
            }
            break;
            case ist::IMPR:
                std::cout << dados[s] << '\n';
            break;
            case ist::LEIT: {
                std::cout << ": ";
                std::cin >> dados[s];
            }
            break;
            case ist::ALME:
                s += int(param);
            break;
            case ist::INPP:
            break;
            case ist::PARA:
                std::exit(0);
            break;
            case ist::PARAM: {
                dados[++s] = dados[int(param) + offset];
            }
            break;
            case ist::PUSHER: {
                uint32_t new_i = int(param);
                base[b + 0] = new_i;
                base[b + 1] = s;
                base[b + 2] = c;
                b += 3;
            }
            break;
            case ist::CHPR: {
                c = b;
                i = int(param);
            }
            break;
            case ist::DESM: {
                s = int(s - param);
            }
            break;
            case ist::RTPR: {
                double rt_value = dados[s];
                i = base[c - 3];
                s = base[c - 2];
                c = base[c - 1];
                b -= 3;
                dados[s] = rt_value;
            }
            break;
            default: {
                std::cerr << "Instrução inesperada: " << code << "\n";
                i = codigo.size();
            }
        }
        i++;
        if(i >= codigo.size()) {
            std::cerr << "Falha de segmentação.\n";
            break;
        }
        if(s >= dados.size() || b >= dados.size()) {
            std::cerr << "Estouro de pilha.\n";
        }
    }
}


double compare(double left, double right, uint32_t type) {
    switch (type) {
        case ist::CPIG:
            return left == right;
        case ist::CPME:
            return left < right;
        case ist::CPMI:
            return left <= right;
        case ist::CPMA:
            return left > right;
        case ist::CMAI:
            return left >= right;
        default:
            return 0;
    }
}

double operation(double left, double right, uint32_t type) {
    switch (type) {
        case ist::SOMA:
            return left + right;
        case ist::SUBT:
            return left - right;
        case ist::MULT:
            return left * right;
        case ist::DIVI:
            return left / right;
        default:
            return 0;
    }
}

double logic_op(double left, double right, uint32_t type) {
    switch (type) {
        case ist::CONJ:
            return int(left) && int(right);
        case ist::DISJ:
            return int(left) || int(right);
        default:
            return 0;
    }
}