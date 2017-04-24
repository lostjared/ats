#ifndef __FUNCTION_HPP_
#define __FUNCTION_HPP_

#include<string>
#include<iostream>
#include<vector>
#include"code.hpp"
#include<unordered_map>

extern interp::Code code;
typedef void (*tokenFunc)(const std::string &command, std::vector<lex::Token> &tokens);
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
    void token_Convert(const std::string &command, std::vector<lex::Token> &tokens);
    void token_List(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Save(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Open(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Clear(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Remove(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Display(const std::string &command, std::vector<lex::Token> &tokens);
    void token_DisplaySymbols(const std::string &command, std::vector<lex::Token> &tokens);
    void token_DisplaySymbol(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Unsym(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Execute(const std::string &command, std::vector<lex::Token> &tokens);
    void token_Help(const std::string &command, std::vector<lex::Token> &tokens);
    void token_sh(const std::string &command, std::vector<lex::Token> &tokens);
    void token_HTML(const std::string &command, std::vector<lex::Token> &tokens);
    void token_ProcInfo(const std::string &command, std::vector<lex::Token> &tokens);
}

#endif
