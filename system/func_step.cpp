#include "function.hpp"


namespace token {
    void token_Step(const std::string &cmd, std::vector<lex::Token> &tokens) {
        if(code.instruct.size()==0) {
            std::cerr << "Error: You must run build first.\n";
            return;
        }
        code.printCurrent();
        code.step();
        std::cout << "Registers: \n";
        code.print();
    }
}
