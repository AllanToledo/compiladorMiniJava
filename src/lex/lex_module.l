%{
#include <vector>
#include <string>
#include "lex.h"

#define YY_DECL int yylex (std::vector<lex::token> &t)
%}

letter          [a-zA-Z]
digit           [0-9]
digits          {digit}{digit}*
option_fraction (\.{digits})?
option_exponent (E[+-]?{digits})?
keyword         while|if|else|return|void|double|public|static|class
identifier      ({letter}({letter}|{digit}|"_")*)
num             {digits}{option_fraction}{option_exponent}
selftoken       [\(\)\{\}\[\]\=\;\,]
relop           (\<|\>|\<\=|\>\=|\=\=|\!\=)

%%
{keyword}       {t.emplace_back(lex::KEYWORD,    std::string(yytext));}
{identifier}    {t.emplace_back(lex::IDENTIFIER, std::string(yytext));}
{num}           {t.emplace_back(lex::NUM,        std::string(yytext));}
[+-]            {t.emplace_back(lex::ADD_OP,     std::string(yytext));}
[\*\/]          {t.emplace_back(lex::MULT_OP,    std::string(yytext));}
{relop}         {t.emplace_back(lex::REL_OP,     std::string(yytext));}
"&&"            {t.emplace_back(lex::AND_OP,     std::string(yytext));}
"||"            {t.emplace_back(lex::OR_OP,      std::string(yytext));}
"!"/^"="        {t.emplace_back(lex::NEG_OP,     std::string(yytext));}
{selftoken}     {t.emplace_back(lex::SELF,       std::string(yytext));}
[ \t\n]
.               {t.emplace_back(lex::ERROR, std::string(yytext));}
%%

int yywrap() {}
std::vector<lex::token> lex::get_tokens(const std::string &file){
    std::vector<lex::token> tokens;
    yyin = fopen(file.c_str(), "r");
    yylex(tokens);
    return std::move(tokens);
}
