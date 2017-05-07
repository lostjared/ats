#include "function.hpp"

namespace token {
    
    void token_Peek16(const std::string &cmd, std::vector<lex::Token> &tokens) {
        unsigned int address = icode::toHex(tokens[1].getToken());
        if(address > 0xFFFE) {
            std::cerr << "Error: out of memory bounds..\n";
            return;
        }
        uint16_t val;
        uint8_t *ptr = (uint8_t *)&val;
        ptr[0] = code.peek(address);
        ptr[1] = code.peek(address+1);
        
        std::cout << "[ $" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << address << ":" << "$" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << address+1 << " = [ $" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << val << " : " << std::dec << val << " ]\n";
        
    }
    
}
