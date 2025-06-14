#include "function.hpp"

namespace token {
    
    void token_Peek16(const std::string &cmd, std::vector<lex::Token> &tokens) {
        unsigned int address = icode::toHex(tokens[1].getToken());
        if(address > 0xFFFE) {
            std::cerr << "Error: out of memory bounds..\n";
            return;
        }
        
        uint8_t lo = code.peek(address);     
        uint8_t hi = code.peek(address + 1); 
        uint16_t value = (static_cast<uint16_t>(hi) << 8) | lo;
        
        std::cout << "[ $" 
                << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << address 
                << ":$" 
                << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << (address + 1)
                << " = [ $" 
                << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(lo)
                << " $"
                << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(hi)
                << " ] -> $"
                << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << value
                << " | #" << std::dec << value
                << " ]\n";
    }
    
}
