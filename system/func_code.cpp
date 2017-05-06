#include "function.hpp"
#include "code.hpp"

namespace token {
    void token_Code(const std::string &cmd, std::vector<lex::Token> &tokens) {
        if(code.instruct.size()==0) {
            std::cerr << "Error: you must use build command first.\n";
            return;
        }
        std::cout << "Hex: ";
        unsigned int i;
        for(i = 0; i < code.instruct.size(); ++i) {
            std::string hextext = icode::instructionToHex(code.instruct[i]);
            std::cout << hextext;
        }
        std::cout << "\nBinary: ";
        for(i = 0; i < code.instruct.size(); ++i) {
            std::string bintext = icode::instructionToBinary(code.instruct[i]);
            std::cout << bintext;
        }
        std::cout << "\n";
    }
}
