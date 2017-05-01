#include "function.hpp"
#include "translate.hpp"

namespace token {
    
    void token_Execute(const std::string &command, std::vector<lex::Token> &tokens) {
        if(translate::build_code()==true) {
            std::cout << "Successfully build code...\n";
        }
    }
    
}
