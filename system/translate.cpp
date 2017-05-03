#include "translate.hpp"
#include "function.hpp"


namespace translate {
    
    bool confirm_mode(const icode::opc code, unsigned int mode, unsigned char &op_byte) {
        for(unsigned int i = 0; interp::m_code[i].p_code != icode::opc::NOTINC; ++i) {
            if(interp::m_code[i].p_code == code && interp::m_code[i].address_mode == mode) {
                op_byte = interp::m_code[i].op_code;
                return true;
            }
        }
        op_byte = 0;
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
        inst.line_num = line_value;
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
                if(confirm_mode(inst.opcode, interp::IMPLIED, inst.op_byte)==false) {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not valid in implied address mode.\n";
                    throw cExcep(stream.str());
                }
                inst.mode = interp::IMPLIED;
            }
                break;
            case 1:
                switch(tokens[1].getTokenType()) {
                    case lex::TOKEN_DIGIT: {
                        if(confirm_mode(inst.opcode, interp::RELATIVE, inst.op_byte) == false) {
                            std::ostringstream stream;
                            stream << "Error on Line: " << line_value << " instruction " << inst.opcode << " not supported in relative addressing mode.\n";
                            throw cExcep(stream.str());
                        } else {
                            unsigned int label_value = atoi(tokens[1].getToken().c_str());
                            inst.op1 = icode::Operand(label_value, icode::op_type::OP_LABEL);
                            inst.mode = interp::RELATIVE;
                        }
                    }
                        break;
                    case lex::TOKEN_HEX: {
                        if(confirm_mode(inst.opcode, interp::ABSOULTE, inst.op_byte) == false) {
                            
                            std::ostringstream stream;
                            stream << "Error on Line: " << line_value << " " << inst.opcode << " not supported in absoulte addressing mode.\n";
                            throw cExcep(stream.str());
                        }
                        unsigned int hex_address = icode::toHex(tokens[1].getToken());
                        inst.op1 = icode::Operand(hex_address, icode::op_type::OP_MEMORY);
                        inst.mode = interp::ABSOULTE;
                    }
                        break;
                    case lex::TOKEN_CHAR:
                        // check if label exisits
                        if(confirm_mode(inst.opcode, interp::RELATIVE, inst.op_byte) == false) {
                            std::ostringstream stream;
                            stream << "Error on Line: " << line_value << " instruction " << inst.opcode << " does not support relative addressing mode.\n";
                        }
                        inst.op1 = icode::Operand(0, icode::op_type::OP_LABELTEXT);
                        inst.op1.label_text = tokens[1].getToken();
                        inst.mode = interp::RELATIVE;
                        break;
                    default:
                        break;
                }
                
                break;
            case 2:
                
                switch(tokens[1].getTokenType()) {
                    case lex::TOKEN_OPERATOR: {
                        if(tokens[1].getToken() == "#") {
                         
                            unsigned int numeric_value = 0;
                            
                            if(tokens[2].getTokenType() == lex::TOKEN_DIGIT) {
                                numeric_value = atoi(tokens[2].getToken().c_str());
                                
                            } else if(tokens[2].getTokenType() == lex::TOKEN_HEX) {
                                numeric_value = icode::toHex(tokens[2].getToken());
                            } else {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " Deicmal or Hex value expected..\n";
                                throw cExcep(stream.str());
                            }
                            
                            if(confirm_mode(inst.opcode, interp::IMMEDIATE, inst.op_byte) == false) {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " instruction " << inst.opcode << " not supported in immediate addressing mode.\n";
                                throw cExcep(stream.str());
                            }
                            
                            if(numeric_value > 255) {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " operand is a single byte (no greater than 255).\n";
                                throw cExcep(stream.str());
                            }
                            
                            inst.op1 = icode::Operand(numeric_value, icode::op_type::OP_DECIMAL);
                            inst.mode = interp::IMMEDIATE;
                            
                        } else {
                            std::ostringstream stream;
                            stream << "Error on Line: " << line_value << " Expected # operator..\n";
                            throw cExcep(stream.str());
                        }
                    }
                        break;
                    default:
                        break;
                }
                break;
            case 3: {
                std::string reg = icode::lcase(tokens[3].getToken());
                switch(tokens[1].getTokenType()) {
                    case lex::TOKEN_HEX: {
                        
                        match(tokens[2], lex::TOKEN_OPERATOR);
                        match(tokens[2], ",");
                        
                        if(tokens[2].getToken() == "," && reg == "x") {
                            if(confirm_mode(inst.opcode, interp::ABSOULTE_X, inst.op_byte)==false) {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " instruction " << inst.opcode << " has X register but not supported in absoulte x address mode.\n";
                                throw cExcep(stream.str());
                                
                            }
                            inst.mode = interp::ABSOULTE_X;
                        }
                        if(tokens[2].getToken() == "," && reg == "y") {
                            if(confirm_mode(inst.opcode, interp::ABSOULTE_Y,inst.op_byte)==false) {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " instruction " << inst.opcode << " has Y register but not supported in absoulte y address mode.\n";
                                throw cExcep(stream.str());
                            }
                            inst.mode = interp::ABSOULTE_Y;
                        }
                        unsigned int hex_value = icode::toHex(tokens[1].getToken());
                        inst.op1 = icode::Operand(hex_value, icode::op_type::OP_MEMORY);
                    }
                        break;
                    default: {
                        
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " instruction " << inst.opcode << " requires address value.\n";
                        throw cExcep(stream.str());
                        
                    }
                        break;
                }
                
            }
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
