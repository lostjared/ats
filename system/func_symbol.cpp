#include "function.hpp"

namespace token {
    void token_DisplaySymbol(std::vector<lex::Token> &tokens) {
        if(tokens[1].getTokenType() == lex::TOKEN_CHAR) {
            if(code.symbols.exisits(tokens[1].getToken())) {
                std::cout << code.symbols[tokens[1].getToken()] << "\n";
            } else {
                std::cout << "Error symbol: " << tokens[1].getToken() << " not found\n";
            }
        } else {
            std::cout << "symbol: requires an argument of a valid symbol\n";
        }
    }
}
