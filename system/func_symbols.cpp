#include "function.hpp"

namespace token {
    
    void token_DisplaySymbols(std::vector<lex::Token> &tokens) {
        std::cout << "Symbol Table: \n" << code.symbols << "\n";
    }
    
}
