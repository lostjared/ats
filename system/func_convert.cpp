#include "function.hpp"

namespace token {
    void token_Convert(const std::string &command, std::vector<lex::Token> &v) {
        code.clear();
        for(unsigned int i = 0; i < interp::lines.size(); ++i) {
            if(procLine(interp::lines.at(i), code) == false)
                std::cerr << "Line: " << std::dec << interp::lines.at(i).index << " contains errors.\n";
        }
    }
}
