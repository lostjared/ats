#include "function.hpp"

namespace token {
    void token_List(const std::string &command, std::vector<lex::Token> &v) {
        for(auto i = interp::lines.begin(); i != interp::lines.end(); ++i) {
            std::cout << std::dec << i->index << " " << i->text << "\n";
        }
    }

}
