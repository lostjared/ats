#include "function.hpp"

namespace token {
    void token_SetSym(const std::string &command, std::vector<lex::Token> &tokens) {
        if(tokens[1].getTokenType() != lex::TOKEN_CHAR) {
            std::cerr << "Error: Command requires variable name.\n";
            return;
        }
        std::string var_name = tokens[1].getToken();
        if(!code.symbols.exisits(tokens[1].getToken())) {
            code.symbols[var_name].create(var_name, symbol::Value("", 0));
        }
        std::string var_value = tokens[2].getToken();
        
        if(!(tokens[2].getTokenType() == lex::TOKEN_OPERATOR && var_value == "-") && tokens.size()>=4) {
            std::cerr << "Error: Requires two arguments: var value..\n";
            return;
        }
        switch(tokens[2].getTokenType()) {
            case lex::TOKEN_CHAR:
                if(!code.symbols.exisits(tokens[2].getToken())) {
                    std::cerr << "Error: " << tokens[2].getToken() << " not found!\n";
                    return;
                }
                code.symbols[var_name].setValue(code.symbols[var_value].getValue());
                break;
            case lex::TOKEN_STRING:
                code.symbols[var_name].setValue(symbol::Value(var_value, 0));
                break;
            case lex::TOKEN_HEX:
                code.symbols[var_name].setValue(symbol::Value(var_value, icode::toHex(var_value)));
                break;
            case lex::TOKEN_DIGIT:
                code.symbols[var_name].setValue(symbol::Value(var_value, atof(tokens[2].getToken().c_str())));
                break;
            case lex::TOKEN_OPERATOR:
                if(tokens.size()==4 && var_value == "-" && tokens[3].getTokenType() == lex::TOKEN_DIGIT) {
                    std::string tok_value = "-"+tokens[3].getToken();
                    code.symbols[var_name].setValue(symbol::Value(tok_value, atof(tok_value.c_str())));
                    return;
                }
            default:
                std::cerr << "Error: requires variable/digit/string.\n";
                return;
        }
    }
}
