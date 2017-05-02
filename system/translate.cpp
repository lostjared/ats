#include "translate.hpp"
#include "function.hpp"


namespace translate {
    
    bool confirm_mode(const icode::opc code, unsigned int mode) {
        for(unsigned int i = 0; interp::m_code[i].p_code != icode::opc::NOTINC; ++i) {
            if(interp::m_code[i].p_code == code && interp::m_code[i].address_mode == mode)
                return true;
        }
        return false;
    }
    
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
            std::cerr << e.err;
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
        if(op == icode::opc::NOTINC) {
            inst.label = true;
            inst.label_text = tokens[0].getToken();
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
        
        
        if(inst.label == true) {
            tokens.erase(tokens.begin());
        }
        
        unsigned int tok_size = tokens.size()-1;
        
        switch(tok_size) {
            case 0: {
                if(confirm_mode(inst.opcode, interp::IMPLIED)==false) {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not valid in implied address mode.\n";
                    throw cExcep(stream.str());
                }
                inst.mode = interp::IMPLIED;
            }
                break;
            //todo fill in each case:
            case 1:
                std::cout << "1: " << tokens[1] << "\n";
                break;
            case 2:
                std::cout << "2: " << tokens[2] << "\n";
                break;
            case 3:
                std::cout << "3: " << tokens[3] << "\n";
                break;
            case 4:
                std::cout << "4: " << tokens[4] << "\n";
                break;
            default:
                std::cout << "Default: " << tok_size << "\n";
                break;
        }
        
        code.instruct.push_back(inst);
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
