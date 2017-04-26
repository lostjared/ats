#include "function.hpp"


namespace token {
    
    void token_Poke(const std::string &command, std::vector<lex::Token> &tokens) {
        
        if(tokens[1].getTokenType() != lex::TOKEN_HEX) {
            std::cerr << "Error: command requires hex value as first argument\n";
            return;
        }
        
        if(tokens[2].getTokenType() != lex::TOKEN_HEX) {
            std::cerr << "Error: command requires hex value as second argument\n";
            return;
        }
        
        uint32_t val1, val2;
        
        val1 = icode::toHex(tokens[1].getToken());
        
        if(val1 > 0xFFFF) {
            std::cerr << "Error: First argument must be 16 bit value\n";
            return;
        }
        
        val2 = icode::toHex(tokens[2].getToken());
        
        if(val2 > 0xFF) {
            std::cerr << "Error: second argument must be 8 bit value\n";
            return;
        }
        
        code.poke(static_cast<uint16_t>(val1),static_cast<uint8_t>(val2));
    }
}
