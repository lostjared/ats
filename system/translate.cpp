#include "translate.hpp"

namespace translate {
    
    bool build_code() {
        try {
            if(interp::lines.size()==0) {
                std::cerr << "Error: No code to build...\n";
                return false;
            }
            
            for(unsigned int i = 0; i < interp::lines.size(); ++i) {
                if(build_line(i)==false) {
                    std::cout << "Error on line: " << interp::lines[i].index << "\n";
                    return false;
                }
            }
            
            return true;
        }
        catch(const cExcep &e) {
            
        }
        
        return false;
    }
    
    bool build_line(unsigned int line) {
        std::vector<lex::Token> tokens;
        unsigned int line_value = interp::lines[line].index;
        tokenize_line(interp::lines[line].text, tokens);
        icode::Instruction inst;
        match(tokens[0], lex::TOKEN_CHAR);
        icode::opc op;
        op = icode::strtoInc(tokens[0].getToken());
        unsigned int code_offset = 0;
        if(op == icode::opc::NOTINC) {
            inst.label = true;
            inst.label_text = tokens[0].getToken();
            code_offset = 1;
            match(tokens[1], lex::TOKEN_CHAR);
            icode::opc op_code;
            op_code = icode::strtoInc(tokens[1].getToken());
            if(op_code == icode::opc::NOTINC) {
                std::ostringstream stream;
                stream << "Error: Line: " << line_value << "Expected instruction instead found: " << tokens[1].getToken() << "\n";
                throw cExcep(stream.str());
            } else {
                inst.opcode = op_code;
            }
        } else {
            inst.opcode = op;
        }
        
        return true;
    }
    
    void tokenize_line(const std::string &text, std::vector<lex::Token> &tokens) {
        std::istringstream stream(text);
        lex::Scanner scan(stream);
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            if(token.getTokenType() != lex::TOKEN_EOF)
                tokens.push_back(token);
        }
    }
    
    void match(const lex::Token &token, const lex::Token_type &type) {
        if(token.getTokenType() != type) {
            std::ostringstream stream;
            stream << "Expected Type: " << type << "\n";
            throw cExcep(stream.str());
        }
    }
    
    void match(const lex::Token &token, const std::string &text) {
        if(token.getToken() != text){
            std::ostringstream stream;
            stream << "Expected: " << text << " found: " << token.getToken() << "\n";
            throw cExcep (stream.str());
        }
    }
}
