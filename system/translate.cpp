#include "translate.hpp"
#include "function.hpp"

namespace translate {
    
    std::string last_build_error;

    bool confirm_mode(const icode::opc code, unsigned int mode, unsigned char &op_byte) {
        for(unsigned int i = 0;  interp::m_code[i].p_code != icode::opc::NOTINC; ++i) {
            if(interp::m_code[i].p_code == code && interp::m_code[i].address_mode == mode) {
                op_byte = interp::m_code[i].op_code;
                return true;
            }
        }
        op_byte = 0;
        return false;
    }
    
    bool check_labels() {
        for(unsigned int ix = 0; ix < code.instruct.size(); ++ix) {
            icode::Instruction &i = code.instruct.at(ix);
            if(i.op1.op_t == icode::op_type::OP_LABELTEXT) {
                auto valid = interp::label_table.find(i.op1.label_text);
                if(valid == interp::label_table.end()) {
                    std::cerr << "Error could not find label: " << i.op1.label_text << "\n";
                    return false;
                }
                i.op1.label_index = valid->second;
            } else if(i.op1.op_t == icode::op_type::OP_LABEL) {
                auto valid = interp::label_line_table.find(i.op1.op);
                if(valid == interp::label_line_table.end()) {
                    std::cerr << "Error line number: " << i.op1.op << " does not exist.\n";
                    return false;
                }
                i.op1.label_index = valid->second;
            }
        }
        return true;
    }
    
    bool build_code() {
        try {
            if(!interp::comp_err.str().empty()) {
                return false;
            }

            if(interp::lines.size()==0) {
                last_build_error = "No code to build.";
                std::cerr << "Error: No code to build...\n";
                return false;
            }
            
            if(!interp::label_table.empty())
                interp::label_table.erase(interp::label_table.begin(), interp::label_table.end());
            if(!interp::label_line_table.empty())
                interp::label_line_table.erase(interp::label_line_table.begin(), interp::label_line_table.end());
            
            for(unsigned int i = 0; i < interp::lines.size(); ++i) {
                if(build_line(i)==false) {
                    std::ostringstream oss;
                    oss << "Error on line: " << interp::lines.at(i).index;
                    last_build_error = oss.str();
                    std::cout << last_build_error << "\n";
                    return false;
                }
            }
            if(check_labels() == false) {
                last_build_error = "Label check failed.";
                return false;
            }
            last_build_error.clear();
            return true;
        }
        catch(const cExcep &e) {
            last_build_error = e.err;
            std::cerr << e.err;
        }
        catch(const std::exception &e) {
            last_build_error = e.what();
            std::cerr << e.what();
        }
        catch(...) {
            last_build_error = "Unknown build error.";
            std::cerr << "Unknown build error.\n";
        }
        return false;
    }
    
    
    bool parse_indirect_addressing(const std::vector<lex::Token> &tokens, icode::Instruction &inst, unsigned int line_value) {
        if (tokens.size() < 4) { 
            std::ostringstream stream;
            stream << "Error on Line: " << line_value << " Incomplete indirect addressing syntax.\n";
            throw cExcep(stream.str());
            return false;
        }

        
        if (tokens[1].getToken() != "(") {
            std::ostringstream stream;
            stream << "Error on Line: " << line_value << " Expected '(' for indirect addressing.\n";
            throw cExcep(stream.str());
            return false;
        }

        
        if (tokens[2].getTokenType() != lex::TOKEN_HEX && tokens[2].getTokenType() != lex::TOKEN_DIGIT) {
            std::ostringstream stream;
            stream << "Error on Line: " << line_value << " Expected address inside parentheses.\n";
            throw cExcep(stream.str());
            return false;
        }

        
        unsigned int address = 0;
        std::string addressStr = tokens[2].getToken();
        
        if (tokens[2].getTokenType() == lex::TOKEN_HEX) {
            if (addressStr[0] == '$') {
                addressStr = addressStr.substr(1); 
            }
            address = std::stoul(addressStr, nullptr, 16);
        } else {
            address = std::stoul(addressStr, nullptr, 10);
        }

        if (tokens[3].getToken() == ")") {
            if (tokens.size() > 4) {
                
                if (tokens.size() > 5 && tokens[4].getToken() == "," && 
                    (tokens[5].getToken() == "Y" || tokens[5].getToken() == "y")) {
                    
                    if (address > 0xFF) {
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " Address for (address),Y mode must be in zero page (0-255).\n";
                        throw cExcep(stream.str());
                        return false;
                    }
                    
                    if (!confirm_mode(inst.opcode, interp::INDIRECT_I, inst.op_byte)) {
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " instruction " 
                            << icode::op_array[static_cast<unsigned int>(inst.opcode)] 
                            << " does not support (address),Y addressing.\n";
                        throw cExcep(stream.str());
                        return false;
                    }
                    
                    inst.mode = interp::INDIRECT_I;
                    inst.op1 = icode::Operand(address, icode::op_type::OP_MEMORY);
                    return true;
                } 
            } else {
                if (inst.opcode != icode::opc::JMP) {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value << " Only JMP supports (address) addressing.\n";
                    throw cExcep(stream.str());
                    return false;
                }
                
                if (!confirm_mode(inst.opcode, interp::INDIRECT, inst.op_byte)) {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value << " Instruction does not support indirect addressing.\n";
                    throw cExcep(stream.str());
                    return false;
                }
                
                inst.mode = interp::INDIRECT;
                inst.op1 = icode::Operand(address, icode::op_type::OP_MEMORY);
                return true;
            }
        } 
        else if (tokens[3].getToken() == "," && 
                (tokens.size() > 4 && (tokens[4].getToken() == "X" || tokens[4].getToken() == "x")) && 
                (tokens.size() > 5 && tokens[5].getToken() == ")")) {
            
            if (address > 0xFF) {
                std::ostringstream stream;
                stream << "Error on Line: " << line_value << " Address for (address,X) mode must be in zero page (0-255).\n";
                throw cExcep(stream.str());
                return false;
            }
            
            if (!confirm_mode(inst.opcode, interp::INDEXED_I, inst.op_byte)) {
                std::ostringstream stream;
                stream << "Error on Line: " << line_value << " instruction " 
                    << icode::op_array[static_cast<unsigned int>(inst.opcode)] 
                    << " does not support (address,X) addressing.\n";
                throw cExcep(stream.str());
                return false;
            }
            
            inst.mode = interp::INDEXED_I;
            inst.op1 = icode::Operand(address, icode::op_type::OP_MEMORY);
            return true;
        }
        else {
            std::ostringstream stream;
            stream << "Error on Line: " << line_value << " Invalid indirect addressing syntax.\n";
            throw cExcep(stream.str());
            return false;
        }
        
        return false;
    }
    
    bool build_line(unsigned int line) {
        std::vector<lex::Token> tokens;
        unsigned int line_value = interp::lines[line].index;
        interp::label_line_table[line_value] = line;
        tokenize_line(interp::lines[line].text, tokens);
        icode::Instruction inst;
        inst.text = interp::lines[line].text;
        inst.line_num = line_value;
        match(tokens[0], lex::TOKEN_CHAR);
        icode::opc op;
        inst.instruction_text = interp::lines[line].text;
        op = icode::strtoInc(tokens[0].getToken());
        if(op == icode::opc::NOTINC) {
            inst.label = true;
            inst.label_text = tokens[0].getToken();
            inst.label_index = line;  
            interp::label_table[inst.label_text] = code.instruct.size();  
            
            if (tokens.size() <= 1) {
                // This is just a label on its own line
                code.instruct.push_back(inst);
                return true;
            }
            
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
        
        if (tokens.size() >= 4 && 
                tokens[0].getToken() == "JMP" &&
                tokens[1].getToken() == "(" && 
                tokens[3].getToken() == ")") 
            {
             
                inst.opcode = icode::opc::JMP;
                
                
                unsigned int address = 0;
                
                if (tokens[2].getTokenType() == lex::TOKEN_HEX) {
                
                    address = icode::toHex(tokens[2].getToken());
                } 
                else if (tokens[2].getTokenType() == lex::TOKEN_DIGIT) {
                
                    address = std::stoul(tokens[2].getToken(), nullptr, 10);
                }
                else {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value 
                        << " Invalid address in JMP indirect: expected hex or decimal.\n";
                    throw cExcep(stream.str());
                }
                
                
                if (!confirm_mode(inst.opcode, interp::INDIRECT, inst.op_byte)) {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value 
                        << " JMP does not support indirect addressing.\n";
                    throw cExcep(stream.str());
                }
                
                inst.mode = interp::INDIRECT;
                inst.op1 = icode::Operand(address, icode::op_type::OP_MEMORY);
                code.instruct.push_back(inst);
                return true;
            }

        
        if (tokens.size() > 1 && tokens[1].getToken() == "(") {
            bool rt_val = parse_indirect_addressing(tokens, inst, line_value);
            if(rt_val) {
                code.instruct.push_back(inst);
                return rt_val;
            }
        
        }
        unsigned int tok_size = tokens.size()-1;
        
        switch(tok_size) {
            case 0: {
                
                if (inst.opcode == icode::opc::ASL || inst.opcode == icode::opc::LSR ||
                    inst.opcode == icode::opc::ROL || inst.opcode == icode::opc::ROR) {
                    
                    if(confirm_mode(inst.opcode, interp::ACCUMULATOR, inst.op_byte) == false) {
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not valid in accumulator address mode.\n";
                        throw cExcep(stream.str());
                    }
                    inst.mode = interp::ACCUMULATOR;
                    inst.op1 = icode::Operand(0, icode::op_type::OP_REGISTER_A);
                }
                
                else if(confirm_mode(inst.opcode, interp::IMPLIED, inst.op_byte) == false) {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not valid in implied address mode.\n";
                    throw cExcep(stream.str());
                } else {
                    inst.mode = interp::IMPLIED;
                }
            }
                break;
            case 1:
                switch(tokens[1].getTokenType()) {
                    case lex::TOKEN_DIGIT: {
                        
                        if(confirm_mode(inst.opcode, interp::RELATIVE, inst.op_byte) == false) {
                            if(confirm_mode(inst.opcode, interp::ABSOULTE, inst.op_byte) == true) {
                                inst.mode = interp::ABSOULTE;
                            } else {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not supported in relative addressing mode.\n";
                                throw cExcep(stream.str());
                            }
                        } else
                        inst.mode = interp::RELATIVE;
                        unsigned int label_value = atoi(tokens[1].getToken().c_str());
                        inst.op1 = icode::Operand(label_value, icode::op_type::OP_LABEL);
                    }
                        break;
                    case lex::TOKEN_HEX: {
                        
                        if(confirm_mode(inst.opcode, interp::ABSOULTE, inst.op_byte) == false) {
                            std::ostringstream stream;
                            stream << "Error on Line: " << line_value << " " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not supported in absoulte addressing mode.\n";
                            throw cExcep(stream.str());
                        }
                        unsigned int hex_address = icode::toHex(tokens[1].getToken());
                        if(hex_address <= 255) {
                            inst.op1 = icode::Operand(hex_address, icode::op_type::OP_MEMORY);
                            inst.mode = interp::ZEROPAGE;
                            
                        } else {
                            inst.op1 = icode::Operand(hex_address, icode::op_type::OP_MEMORY);
                            inst.mode = interp::ABSOULTE;
                        }
                    }
                        break;
                    case lex::TOKEN_CHAR:
                        // check if label exisits
                        if(tokens[1].getToken()=="A" && confirm_mode(inst.opcode, interp::ACCUMULATOR, inst.op_byte)==true) {
                            inst.op1 = icode::Operand(0, icode::op_type::OP_REGISTER_A);
                            inst.mode = interp::ACCUMULATOR;
                            break;
                        }
                        else
                        if(confirm_mode(inst.opcode, interp::ABSOULTE, inst.op_byte) == false) {
                            
                            if(confirm_mode(inst.opcode, interp::RELATIVE, inst.op_byte) == true) {
                                inst.mode = interp::RELATIVE;
                            } else {
                                std::ostringstream stream;
                                stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " does not support addressing mode.\n";
                                throw cExcep(stream.str());
                            }
                        } else {
                            inst.mode = interp::ABSOULTE;
                        }
                        
                        inst.op1.op_t = icode::op_type::OP_LABELTEXT;
                        inst.op1.label_text = tokens[1].getToken();
                    case lex::TOKEN_OPERATOR: {
                        std::string op = tokens[1].getToken();
                        
                        // For any other operator token, throw an error
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value 
                               << " Unrecognized operator: " << op << "\n";
                        throw cExcep(stream.str());
                    }
                    break;
                    default:
                        break;
                }
                break;
            case 2: {
                if(tokens[1].getToken() == "#") {
                    unsigned int numeric_value = 0;

                    
                    if(tokens[2].getTokenType() == lex::TOKEN_DIGIT) {
                        numeric_value = atoi(tokens[2].getToken().c_str());
                    } else if(tokens[2].getTokenType() == lex::TOKEN_HEX) {
                        numeric_value = icode::toHex(tokens[2].getToken());
                    } else {
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " Decimal or Hex value expected after #.\n";
                        throw cExcep(stream.str());
                    }

                    
                    
                    if(confirm_mode(inst.opcode, interp::IMMEDIATE, inst.op_byte) == false) {
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " not supported in immediate addressing mode.\n";
                        throw cExcep(stream.str());
                    }
                    
                    if(numeric_value > 255) {
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " operand is a single byte (no greater than 255).\n";
                        throw cExcep(stream.str());
                    }
                    
                    inst.op1 = icode::Operand(numeric_value, icode::op_type::OP_DECIMAL);
                    inst.mode = interp::IMMEDIATE;
                    
                }
                else if ((tokens[1].getToken() == "A" || tokens[1].getToken() == "a") &&
                        (inst.opcode == icode::opc::ASL || inst.opcode == icode::opc::LSR ||
                        inst.opcode == icode::opc::ROL || inst.opcode == icode::opc::ROR)) {
                    inst.mode = interp::ACCUMULATOR;
                    inst.op1 = icode::Operand(0, icode::op_type::OP_REGISTER_A);
                }
                else if (interp::isBranchInstruction(inst.opcode)) {
                    if(tokens[1].getTokenType() == lex::TOKEN_DIGIT) {
                        unsigned int label_value = atoi(tokens[1].getToken().c_str());
                        inst.op1 = icode::Operand(label_value, icode::op_type::OP_LABEL);
                        inst.mode = interp::RELATIVE;
                    }
                }
                else {
                    std::ostringstream stream;
                    stream << "Error on Line: " << line_value << " Unrecognized 2-operand instruction format.\n";
                    throw cExcep(stream.str());
                }
            }
            break;
            case 3: {
                std::string reg = icode::lcase(tokens[3].getToken());
                switch(tokens[1].getTokenType()) {
                    case lex::TOKEN_HEX: {
                        
                        unsigned int hex_value = icode::toHex(tokens[1].getToken());
                        match(tokens[2], lex::TOKEN_OPERATOR);
                        match(tokens[2], ",");
                        
                        if(tokens[2].getToken() == "," && reg == "x") {
                            
                            if(confirm_mode(inst.opcode, interp::ABSOULTE_X, inst.op_byte)==false) {
                                if(confirm_mode(inst.opcode, interp::ZEROPAGE_X, inst.op_byte)) {
                                    inst.mode = interp::ZEROPAGE_X;
                                } else {
                                    std::ostringstream stream;
                                    stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " has X register but not supported in absoulte X address mode.\n";
                                    throw cExcep(stream.str());
                                }
                            }
                            
                            if(hex_value > 0xFF)
                                inst.mode = interp::ABSOULTE_X;
                            else
                                inst.mode = interp::ZEROPAGE_X;
                        }
                        if(tokens[2].getToken() == "," && reg == "y") {
                            if(confirm_mode(inst.opcode, interp::ABSOULTE_Y,inst.op_byte)==false) {
                                if(confirm_mode(inst.opcode, interp::ZEROPAGE_Y, inst.op_byte)) {
                                    inst.mode = interp::ZEROPAGE_Y;
                                } else {
                                    std::ostringstream stream;
                                    stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " has Y register but not supported in absoulte y address mode.\n";
                                    throw cExcep(stream.str());
                                }
                            }
                            
                            if(hex_value <= 255)
                                inst.mode = interp::ZEROPAGE_Y;
                            else
                                inst.mode = interp::ABSOULTE_Y;
                        }
                        inst.op1 = icode::Operand(hex_value, icode::op_type::OP_MEMORY);
                    }
                        break;
                    default: {
                        
                        std::ostringstream stream;
                        stream << "Error on Line: " << line_value << " instruction " << icode::op_array[static_cast<unsigned int>(inst.opcode)] << " requires address value.\n";
                        throw cExcep(stream.str());
                    }
                        break;
                }
            }
                break;
            default:
                std::ostringstream stream;
                stream << "Error on Line: " << line_value << " Unsupported addressing format (tokens: " << tok_size + 1 << ").\n";
                throw cExcep(stream.str());
                return false;
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
            stream << "Type Expected: " << type << " found: " << token.getTokenType() << "\n";
            throw cExcep(stream.str());
        }
    }
    
    void match(const lex::Token &token, const std::string &text) {
        if(token.getToken() != text) {
            std::ostringstream stream;
            stream << "Type Expected: " << text << " found: " << token.getToken() << "\n";
            throw cExcep(stream.str());
        }
    }
}