#include"function.hpp"


namespace token {
    
    void token_SetReg(const std::string &command, std::vector<lex::Token> &tokens) {
        std::string reg = icode::lcase(tokens[1].getToken());
        uint32_t val;
        if(tokens[2].getTokenType() == lex::TOKEN_HEX)
            val = icode::toHex(tokens[2].getToken());
        else if(tokens[2].getTokenType() == lex::TOKEN_DIGIT)
            val = atoi(tokens[2].getToken().c_str());
        else {
            std::cerr << "Error: setreg requires decimal or hex argument.\n";
            return;
        }
        if(val > 255) {
            std::cerr << "Error: x,y,a,p registers are 8 bits.\n";
            return;
        }
        
        if(reg == "x")
            code.proc.reg_x = val;
		 else if(reg == "y")
            code.proc.reg_y = val;
        else if(reg == "a")
            code.proc.reg_a = val;
        else if(reg == "p")
            code.proc.setFlags(val);
        
    }
}
