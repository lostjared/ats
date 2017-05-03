#include "function.hpp"
#include "code.hpp"

namespace token {
    
    void token_Print(const std::string &cmd, std::vector<lex::Token> &tokens) {
        if(code.instruct.size()==0) {
            std::cerr << "Error: execute build command first.\n";
            return;
        }
        for(unsigned int i =0; i < code.instruct.size(); ++i) {
            std::cout << code.instruct[i] << "\n";
        }
    }
}
