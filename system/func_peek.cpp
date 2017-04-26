#include "function.hpp"

namespace token {
    
    void token_Peek(const std::string &command, std::vector<lex::Token> &tokens) {
        if(tokens[1].getTokenType() != lex::TOKEN_HEX) {
            std::cerr << "Error: requires hex constant argumnet.\n";
            return;
        }
        
        uint32_t val;
        val = icode::toHex(tokens[1].getToken());
        if(val > 0xFFFF) {
            std::cerr << "Error: constant must be 16 bit value.\n";
            return;
        }
        
        std::cout << "[" << std::hex << std::uppercase << val << "] = " << std::hex << std::uppercase << static_cast<int>(code.peek(val)) << "\n";
    }
}
