#include "function.hpp"
#include "translate.hpp"

namespace token {
    
    void token_Build(const std::string &cmd, std::vector<lex::Token> &tokens) {
        code.reset();
        if(translate::build_code()==true) {
            std::cout << "Successfully built code...\n";
        }
    }
    
    
}
