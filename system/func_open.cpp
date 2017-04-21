#include "function.hpp"

namespace token {
    void token_Open(const std::string &command, std::vector<lex::Token> &v) {
        if(v[1].getTokenType() != lex::TOKEN_STRING) {
            std::cerr << "open requires string operand in quotes.\n";
            return;
        }
        std::string filename;
        filename = v[1].getToken();
        if(interp::openLineSource(filename)) {
            std::cout << "Loaded: " << filename << "\n";
        }
    }
}
