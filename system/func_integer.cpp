#include"function.hpp"


namespace token {
    
    void token_Integer(const std::string &cmd, std::vector<lex::Token> &tokens) {
        if(tokens.size() == 1) {
            std::cerr << "Error: Requires values...\n";
            return;
        }
        
        for(unsigned int i = 1; i < tokens.size(); ++i) {
            switch(tokens[i].getTokenType()) {
                case lex::TOKEN_DIGIT: {
                    int value = atoi(tokens[i].getToken().c_str());
                    std::cout << std::dec << value <<  " = [ $" << std::hex << std::uppercase << value << " ]\n";
                }
                    break;
                case lex::TOKEN_HEX: {
                    int value = icode::toHex(tokens[i].getToken());
                    std::cout << "$" << std::hex << std::uppercase << value <<  " = [ " << std::dec << value << " ]\n";
                }
                    break;
                default:
                    break;
            }
            
        }
    }
}
