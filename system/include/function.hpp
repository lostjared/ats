#ifndef __FUNCTION_HPP_
#define __FUNCTION_HPP_

#include<string>
#include<iostream>
#include<vector>
#include"code.hpp"
#include<unordered_map>

extern interp::Code code;
typedef void (*tokenFunc)(std::vector<lex::Token> &tokens);
struct Command {
    int args;
    tokenFunc func;
    Command() = default;
    Command(tokenFunc ifunc, int iargs) {
        args = iargs;
        func = ifunc;
    }
};
extern std::unordered_map<std::string, Command> function_map;

namespace token {
    void token_Convert(std::vector<lex::Token> &tokens);
    void token_List(std::vector<lex::Token> &tokens);
    void token_Save(std::vector<lex::Token> &tokens);
    void token_Open(std::vector<lex::Token> &tokens);
    void token_Clear(std::vector<lex::Token> &tokens);
    void token_Remove(std::vector<lex::Token> &tokens);
    void token_Display(std::vector<lex::Token> &tokens);
    void token_DisplaySymbols(std::vector<lex::Token> &tokens);
    void token_DisplaySymbol(std::vector<lex::Token> &tokens);
    void token_Unsym(std::vector<lex::Token> &tokens);
}

#endif
