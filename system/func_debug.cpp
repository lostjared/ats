#include "function.hpp"


namespace token {
    void token_Debug(const std::string &cmd, std::vector<lex::Token> &tokens) {
        if(code.instruct.size()==0) {
            std::cerr << "Error you must build first.\n";
            return;
        }
        code.start(true);
    }
}
