#include "function.hpp"

namespace token {
    
    void token_Memory(const std::string &cmd, std::vector<lex::Token> &tokens) {
        unsigned int start = 0, stop = 0;
        if(tokens[1].getTokenType() == lex::TOKEN_HEX) {
            start = icode::toHex(tokens[1].getToken());
        } else {
            std::cerr << "Error command argument one is a hex value.\n";
            return;
        }
        if(tokens[2].getTokenType() == lex::TOKEN_HEX) {
            stop = icode::toHex(tokens[2].getToken());
        } else {
            std::cerr << "Error argument two is a hex value.\n";
            return;
        }
        if(start > 0xFFFF || stop > 0xFFFF) {
            std::cerr << "Out of range..\n";
            return;
        }
        if(start < stop) {
            for(unsigned int i = start; i <= stop; ++i) {
                std::cout << "Memory Address: [ $" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i << " ] = [ $" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(code.peek(i)) << " ]\n";
            }
        }
        else {
            std::cerr << "Error: out of range.\n";
        }
    }
    
}
