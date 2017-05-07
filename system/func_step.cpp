#include "function.hpp"


namespace token {
    void token_Step(const std::string &cmd, std::vector<lex::Token> &tokens) {
        code.step();
        code.print();
    }
}
