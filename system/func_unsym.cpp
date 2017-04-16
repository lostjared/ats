#include "function.hpp"

namespace token {
    void token_Unsym(std::vector<lex::Token> &tokens) {
        if(tokens[1].getTokenType() == lex::TOKEN_CHAR) {
            if(code.symbols.exisits(tokens[1].getToken())) {
                code.symbols.remove(tokens[1].getToken());
            } else {
                std::cerr << "Symbol: " << tokens[1].getToken() << " does not exisit\n";
            }
        } else {
            std::cerr << "unsym requires one argument, symbol to remove\n";
        }
    }
}
