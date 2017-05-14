#include"function.hpp"
#include"code.hpp"


namespace token {
    
    void token_Continue(const std::string &cmd, std::vector<lex::Token> &tokens) {
        
        if(code.instruct.size()==0) {
            std::cerr << "Error: requires you run build first.\n";
            return;
        }
        
        code.cont();
    }
    
}
