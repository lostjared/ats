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
        std::cout << "[ $" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << val << " ] = $" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(code.peek(val)) << " | #" << std::dec << static_cast<unsigned int>(code.peek(val)) << "\n";
    }
}
