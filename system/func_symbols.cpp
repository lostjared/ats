#include "function.hpp"

namespace token {
    
    void token_DisplaySymbols(const std::string &command, std::vector<lex::Token> &tokens) {
        std::cout << "Symbol Table: \n" << code.symbols << "\n";
    }
    
}
