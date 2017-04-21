#include "function.hpp"


namespace token {
    
    void token_Help(const std::string &command, std::vector<lex::Token> &tokens) {
        std::cout << "Command list:\nquit\n";
        std::vector<std::string> names;
        for(auto i = function_map.begin(); i != function_map.end(); ++i) {
            names.push_back(i->first);
        }
        std::sort(names.begin(), names.end());
        for(auto i = names.begin(); i != names.end(); ++i) {
            std::cout << *i << "\n";
        }
    }
}
