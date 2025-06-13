#include "code.hpp"

namespace interp {

    std::ostringstream comp_err;
    
    bool saveLineSource(const std::string &text) {
        std::fstream file;
        file.open(text, std::ios::out);
        if(!file.is_open()) return false;
        for(unsigned int i = 0; i < lines.size(); ++i) {
            file << lines[i].index << " " << lines[i].text << "\n";
        }
        file.close();
        return true;
    }
    
    std::string eatComment(std::string src) {
        std::string text;
        for(unsigned int i = 0; i < src.length(); ++i) {
            if(src[i] == ';') return text;
            else
                text += src[i];
        }
        return text;
    }
    
    bool openLineSource(const std::string &text) {
        comp_err.str("");
        std::fstream file;
        file.open(text, std::ios::in);
        if(!file.is_open()) return false;
        
        if(!lines.empty()) {
            lines.clear();
        }
        
        std::string orig;
        while(std::getline(file, orig)) {  
            std::string in = eatComment(orig);
            if(in.length() == 0) continue;
            
            std::vector<lex::Token> tokens;
            std::istringstream stream(in);
            lex::Scanner scan(stream);
            while(scan.valid()) {
                lex::Token token;
                scan >> token;
                if(token.getTokenType() != lex::TOKEN_EOF)
                    tokens.push_back(token);
            }
            
            if(!inputText(tokens, in))
                return false;
        }
        file.close();
        return true;
    }

    bool openLineString(const std::string &text) {
        comp_err.str("");
        std::istringstream file(text);
        if(!lines.empty()) {
            lines.erase(lines.begin(), lines.end());
        }
        std::string orig;
        while(std::getline(file, orig)) {
            std::string in;
            in = eatComment(orig);
            if(in.length()==0) continue;
            std::vector<lex::Token> tokens;
            std::istringstream stream(in);
            lex::Scanner scan(stream);
            while(scan.valid()) {
                lex::Token token;
                scan >> token;
                if(token.getTokenType() != lex::TOKEN_EOF)
                	tokens.push_back(token);
            }   
            if(!inputText(tokens, in))
                return false;
        }
        return true;
    }
    
    void insertText(std::vector<lex::Token> &tokens, const TextLine &in) {
        for(unsigned int i = 0; i < lines.size(); ++i) {
            if(lines[i].index == in.index) {
                lines[i].text = in.text;
                std::sort(lines.begin(), lines.end());
                return;
            }
        }
        lines.push_back(in);
        std::sort(lines.begin(), lines.end());
    }

    bool inputText(std::vector<lex::Token> &tokens, std::string input_line) {
        if(!comp_err.str().empty()) return false;
        if (input_line.empty()) {
            comp_err << "Error: Empty input line.\n";
            return false;
        }
         
        bool hasLineNumber = (tokens.size() >= 1 && tokens[0].getTokenType() == lex::TOKEN_DIGIT);
        
        if (hasLineNumber && tokens.size() >= 2) {
            int value = atoi(tokens[0].getToken().c_str());
            std::string codetext = input_line.substr(input_line.find(tokens[0].getToken()) + tokens[0].getToken().length());
            codetext.erase(0, codetext.find_first_not_of(" \t"));    
            TextLine in(value, codetext);
           
            if (checkInstruction(tokens, in)) {
                insertText(tokens, in);
                return true;
            }
        } else if (!hasLineNumber && tokens.size() >= 1) {
            int generatedLineNumber = 10;
            if (!lines.empty()) {
                int maxLine = 0;
                for (const auto& line : lines) {
                    if (line.index > maxLine) {
                        maxLine = line.index;
                    }
                }
                generatedLineNumber = maxLine + 10;
            }
            
            TextLine in(generatedLineNumber, input_line);
            std::cout << "Creating auto-numbered line: " << generatedLineNumber << " -> '" << input_line << "'\n";
            
            std::vector<lex::Token> tempTokens;
            tempTokens.push_back(lex::Token(std::to_string(generatedLineNumber), lex::TOKEN_DIGIT));
            tempTokens.insert(tempTokens.end(), tokens.begin(), tokens.end());
            
            if (checkInstruction(tempTokens, in)) {
                insertText(tempTokens, in);
                return true;
            }
        } else if (tokens.size() == 1 && hasLineNumber) {
              int index_n = atoi(tokens[0].getToken().c_str());
            for (int i = 0; i < lines.size(); ++i) {
                if (lines[i].index == index_n) {
                    lines.erase(lines.begin() + i);
                    std::cout << "Deleted line " << index_n << std::endl;
                    return true;
                }
            }
            comp_err << "Error: Line " << index_n << " not found.\n";
            return false;
        } else {
            std::cout << "Line rejected - doesn't match any pattern\n";
            comp_err << "Error: Invalid input format for line: " << input_line << "\n";
            return false;
        }
        
        return false;
    }

    bool isBranchInstruction(icode::opc op) {
        return op == icode::opc::BNE || op == icode::opc::BEQ ||
            op == icode::opc::BCC || op == icode::opc::BCS ||
            op == icode::opc::BMI || op == icode::opc::BPL ||
            op == icode::opc::BVC || op == icode::opc::BVS;      
    }


    bool checkInstruction(std::vector<lex::Token> &tokens, const TextLine &text) {
        if (tokens.size() <= 1) {
            comp_err << "Error: Statement requires instruction.\n";
            return false;
                }
       
        static unsigned int inc_offset = 0;
        inc_offset = 0; 
        
        if (tokens.size() >= 2) {
            icode::opc op = icode::strtoInc(tokens[1].getToken());
            
            if (op == icode::opc::NOTINC) {
                if (tokens[1].getTokenType() != lex::TOKEN_CHAR) {
                    comp_err << "Syntax Error: After line number requires either Label or instruction.\n";
                    return false;
                }
                
                inc_offset = 1;
                if (tokens.size() <= 2) {
                    comp_err << "Syntax Error: Label '" << tokens[1].getToken() << "' must be followed by an instruction.\n";
                    return false;
                }
                
                op = icode::strtoInc(tokens[1 + inc_offset].getToken());
                if (op == icode::opc::NOTINC) {
                    comp_err << "Syntax Error: '" << tokens[1 + inc_offset].getToken() << "' is not a valid 6502 instruction.\n";
                    return false;
                }
            }
            
            return validateAddressingMode(tokens, op, inc_offset);
        }
        
        return true;
    }

    bool validateAddressingMode(std::vector<lex::Token> &tokens, icode::opc instruction, unsigned int offset) {
        int instrIndex = 1 + offset; 
    
        std::cout << "=== validateAddressingMode DEBUG ===\n";
        std::cout << "Instruction: " << icode::op_array[static_cast<unsigned int>(instruction)] << "\n";
        std::cout << "Token count: " << tokens.size() << ", instrIndex: " << instrIndex << "\n";
        
        // Handle implied instructions
        if (tokens.size() <= instrIndex + 1) {
            std::cout << "Checking for implied instruction...\n";
            
            if(instruction == icode::opc::END) {
                std::cout << "Found END instruction, terminating validation.\n";
                return true; // END instruction does not require validation
            }

            // Check if this instruction supports implied mode
            if (instruction == icode::opc::CLC || instruction == icode::opc::CLD || 
                instruction == icode::opc::CLI || instruction == icode::opc::CLV ||
                instruction == icode::opc::SEC || instruction == icode::opc::SED ||
                instruction == icode::opc::SEI || instruction == icode::opc::TXA ||
                instruction == icode::opc::TAX || instruction == icode::opc::TAY ||
                instruction == icode::opc::TSX || instruction == icode::opc::TXS ||
                instruction == icode::opc::TYA || instruction == icode::opc::INX ||
                instruction == icode::opc::INY || instruction == icode::opc::DEX ||
                instruction == icode::opc::DEY || instruction == icode::opc::NOP ||
                instruction == icode::opc::PHA || instruction == icode::opc::PHP ||
                instruction == icode::opc::PLA || instruction == icode::opc::PLP ||
                instruction == icode::opc::RTS || instruction == icode::opc::RTI ||
                instruction == icode::opc::BRK) {
                
                std::cout << "Found implied instruction, validating...\n";
                bool result = validateInstructionAddressingMode(instruction, "IMPLIED");
                std::cout << "Implied validation result: " << result << "\n";
                return result;
            }
            // Check if this instruction supports accumulator mode
            else if (instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                     instruction == icode::opc::ROL || instruction == icode::opc::ROR) {
                
                std::cout << "Found accumulator instruction, validating...\n";
                bool result = validateInstructionAddressingMode(instruction, "ACCUMULATOR");
                std::cout << "Accumulator validation result: " << result << "\n";
                return result;
            }
            
            std::cout << "Instruction not recognized as implied or accumulator\n";
            comp_err << "Syntax Error: " << tokens[instrIndex].getToken() << " instruction requires an operand.\n";
            return false;
        }
        
        std::cout << "Has operands, checking addressing modes...\n";
        int operandIndex = instrIndex + 1;
        
        
        if (isBranchInstruction(instruction)) {
            if (tokens[operandIndex].getTokenType() == lex::TOKEN_DIGIT) {
                return validateInstructionAddressingMode(instruction, "RELATIVE");
            } else if (tokens[operandIndex].getTokenType() == lex::TOKEN_CHAR) {        
                return validateInstructionAddressingMode(instruction, "RELATIVE");
            } else {
                comp_err << "Syntax Error: Branch instruction expects line number or label.\n";
                return false;
            }
        }

        if (tokens[operandIndex].getToken() == "#") {
            if (tokens.size() <= operandIndex + 1) {
                comp_err << "Syntax Error: Missing value after #\n";
                return false;
            }
            
            
            if (tokens[operandIndex + 1].getTokenType() != lex::TOKEN_DIGIT && 
                tokens[operandIndex + 1].getTokenType() != lex::TOKEN_HEX) {
                comp_err << "Syntax Error: # must be followed by a number or hex value ($XX).\n";
                return false;
            }
         
            if (tokens.size() > operandIndex + 2) {
                comp_err << "Syntax Error: Immediate addressing (#) cannot be indexed with ,X or ,Y\n";
                return false;
            }
            
            return validateInstructionAddressingMode(instruction, "IMMEDIATE");
        }
        else if (tokens[operandIndex].getToken() == "(" ) {
            return parseIndirectAddressing(tokens, instruction, operandIndex);
        }
        else if (tokens[operandIndex].getTokenType() == lex::TOKEN_HEX || 
                tokens[operandIndex].getTokenType() == lex::TOKEN_DIGIT ||
                tokens[operandIndex].getTokenType() == lex::TOKEN_CHAR) {
            
            std::string addressingMode = "ABSOLUTE";
            
            if (tokens[operandIndex].getTokenType() == lex::TOKEN_HEX) {
                std::string hexValue = tokens[operandIndex].getToken();
                if (hexValue.length() <= 3) { 
                    addressingMode = "ZEROPAGE";
                }
            } else if (tokens[operandIndex].getTokenType() == lex::TOKEN_DIGIT) {
                int value = atoi(tokens[operandIndex].getToken().c_str());
                if (value < 256) {
                    addressingMode = "ZEROPAGE";
                }
            }
            
            if (tokens.size() > operandIndex + 1) {
                if (tokens[operandIndex + 1].getToken() == ",") {
                    if (tokens.size() <= operandIndex + 2) {
                        comp_err << "Syntax Error: Comma must be followed by X or Y register.\n";
                        return false;
                    }
                    
                    std::string reg = tokens[operandIndex + 2].getToken();
                    if (reg == "X" || reg == "x") {
                        addressingMode += "_X";
                    } else if (reg == "Y" || reg == "y") {
                        addressingMode += "_Y";
                    } else {
                        comp_err << "Syntax Error: Only X and Y registers are valid for indexing.\n";
                        return false;
                    }
                } else {
                    comp_err << "Syntax Error: Expected comma before register, found: " << tokens[operandIndex + 1].getToken() << "\n";
                    return false;
                }
            }
            
            return validateInstructionAddressingMode(instruction, addressingMode);
        }
        
        if (tokens[operandIndex].getToken() == "A" || tokens[operandIndex].getToken() == "a") {
            if (instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                instruction == icode::opc::ROL || instruction == icode::opc::ROR) {
                return validateInstructionAddressingMode(instruction, "ACCUMULATOR");
            }
        }
        
        comp_err << "Syntax Error: Invalid operand format.\n";
        return false;
    }

    bool validateInstructionIndirectMode(icode::opc instruction, const std::string& mode) {
        if (mode == "RELATIVE") {
               return isBranchInstruction(instruction);
        }
        if (mode == "INDIRECT") {
            return instruction == icode::opc::JMP;
        }
        if (mode == "INDEXED_INDIRECT") {
            return (instruction == icode::opc::LDA ||
                    instruction == icode::opc::STA ||
                    instruction == icode::opc::CMP ||
                    instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC ||
                    instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA ||
                    instruction == icode::opc::EOR);
        }
        if (mode == "INDIRECT_INDEXED") {
            return (instruction == icode::opc::LDA ||
                    instruction == icode::opc::STA ||
                    instruction == icode::opc::CMP ||
                    instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC ||
                    instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA ||
                    instruction == icode::opc::EOR);
        }
        return false;
    }

    bool parseIndirectAddressing(std::vector<lex::Token> &tokens, icode::opc instruction, int startIndex) {
        if (tokens.size() <= startIndex + 2) {
            comp_err << "Syntax Error: Incomplete indirect addressing mode.\n";
            return false;
        }
    
        if (tokens[startIndex + 1].getTokenType() != lex::TOKEN_HEX && 
            tokens[startIndex + 1].getTokenType() != lex::TOKEN_DIGIT) {
            comp_err << "Syntax Error: Expected address inside parentheses.\n";
            return false;
        }
    
        std::string addressingMode;
    
        if (tokens.size() > startIndex + 2) {
            if (tokens[startIndex + 2].getToken() == ")") {
                if (tokens.size() > startIndex + 3 && tokens[startIndex + 3].getToken() == ",") {
                    if (tokens.size() > startIndex + 4 && 
                        (tokens[startIndex + 4].getToken() == "Y" || tokens[startIndex + 4].getToken() == "y")) {
                        addressingMode = "INDIRECT_INDEXED"; 
                    } else {
                        comp_err << "Syntax Error: Only Y register supported for ),Y addressing.\n";
                        return false;
                    }
                } else {
                    addressingMode = "INDIRECT"; 
                }
            } else if (tokens[startIndex + 2].getToken() == ",") {
                
                if (tokens.size() > startIndex + 3 && 
                    (tokens[startIndex + 3].getToken() == "X" || tokens[startIndex + 3].getToken() == "x")) {
                    if (tokens.size() > startIndex + 4 && tokens[startIndex + 4].getToken() == ")") {
                        addressingMode = "INDEXED_INDIRECT"; // (address,X)
                    } else {
                        comp_err << "Syntax Error: Missing closing parenthesis.\n";
                        return false;
                    }
                } else {
                    comp_err << "Syntax Error: Only X register supported for (,X) addressing.\n";
                    return false;
                }
            }
        }
    
        return validateInstructionIndirectMode(instruction, addressingMode);
    }

    bool validateInstructionAddressingMode(icode::opc instruction, const std::string& mode) {        
        std::cout << "validateInstructionAddressingMode: " << icode::op_array[static_cast<unsigned int>(instruction)] 
                  << " with mode: " << mode << "\n";
                  
        if (mode == "RELATIVE") {
            // Only branch instructions support relative addressing
            bool isRelative = (instruction == icode::opc::BPL ||  // Branch if Plus
                              instruction == icode::opc::BMI ||  // Branch if Minus
                              instruction == icode::opc::BVC ||  // Branch if Overflow Clear
                              instruction == icode::opc::BVS ||  // Branch if Overflow Set
                              instruction == icode::opc::BCC ||  // Branch if Carry Clear
                              instruction == icode::opc::BCS ||  // Branch if Carry Set
                              instruction == icode::opc::BNE ||  // Branch if Not Equal
                              instruction == icode::opc::BEQ);   // Branch if Equal
            
            std::cout << "Relative check result: " << isRelative << "\n";
            return isRelative;
        }
              
        if (mode == "IMPLIED") {
            // List of all instructions that support implied addressing
            bool isImplied = (instruction == icode::opc::CLC || instruction == icode::opc::CLD || 
                             instruction == icode::opc::CLI || instruction == icode::opc::CLV ||
                             instruction == icode::opc::SEC || instruction == icode::opc::SED ||
                             instruction == icode::opc::SEI || instruction == icode::opc::TXA ||
                             instruction == icode::opc::TAX || instruction == icode::opc::TAY ||
                             instruction == icode::opc::TSX || instruction == icode::opc::TXS ||
                             instruction == icode::opc::TYA || instruction == icode::opc::INX ||
                             instruction == icode::opc::INY || instruction == icode::opc::DEX ||
                             instruction == icode::opc::DEY || instruction == icode::opc::NOP ||
                             instruction == icode::opc::PHA || instruction == icode::opc::PHP ||
                             instruction == icode::opc::PLA || instruction == icode::opc::PLP ||
                             instruction == icode::opc::RTS || instruction == icode::opc::RTI);
    
            std::cout << "Implied check result: " << isImplied << "\n";
            return isImplied;
        }
        
        if (mode == "IMMEDIATE") {
            // Most instructions support immediate mode, but not all
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDX || 
                    instruction == icode::opc::LDY || instruction == icode::opc::CMP ||
                    instruction == icode::opc::CPX || instruction == icode::opc::CPY ||
                    instruction == icode::opc::ADC || instruction == icode::opc::SBC ||
                    instruction == icode::opc::AND || instruction == icode::opc::ORA ||
                    instruction == icode::opc::EOR);
        }
        
        if (mode == "ABSOLUTE_X") {
            // Instructions that support X indexing
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDY ||
                    instruction == icode::opc::STA || instruction == icode::opc::STY ||
                    instruction == icode::opc::CMP || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR ||
                    instruction == icode::opc::INC || instruction == icode::opc::DEC ||
                    instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                    instruction == icode::opc::ROL || instruction == icode::opc::ROR);
        }
        
        if (mode == "ZEROPAGE") {
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDX || 
                    instruction == icode::opc::LDY || instruction == icode::opc::STA ||
                    instruction == icode::opc::STX || instruction == icode::opc::STY ||
                    instruction == icode::opc::CMP || instruction == icode::opc::CPX ||
                    instruction == icode::opc::CPY || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR ||
                    instruction == icode::opc::INC || instruction == icode::opc::DEC ||
                    instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                    instruction == icode::opc::ROL || instruction == icode::opc::ROR ||
                    instruction == icode::opc::BIT);
        }
        
        if (mode == "ABSOLUTE") {
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDX || 
                    instruction == icode::opc::LDY || instruction == icode::opc::STA ||
                    instruction == icode::opc::STX || instruction == icode::opc::STY ||
                    instruction == icode::opc::CMP || instruction == icode::opc::CPX ||
                    instruction == icode::opc::CPY || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR ||
                    instruction == icode::opc::INC || instruction == icode::opc::DEC ||
                    instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                    instruction == icode::opc::ROL || instruction == icode::opc::ROR ||
                    instruction == icode::opc::BIT || instruction == icode::opc::JMP ||
                    instruction == icode::opc::JSR);
        }
        
        if (mode == "ZEROPAGE_X") {
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDY ||
                    instruction == icode::opc::STA || instruction == icode::opc::STY ||
                    instruction == icode::opc::CMP || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR ||
                    instruction == icode::opc::INC || instruction == icode::opc::DEC ||
                    instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                    instruction == icode::opc::ROL || instruction == icode::opc::ROR);
        }
        
        if (mode == "ABSOLUTE_X") {
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDY ||
                    instruction == icode::opc::STA || instruction == icode::opc::STY ||
                    instruction == icode::opc::CMP || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR ||
                    instruction == icode::opc::INC || instruction == icode::opc::DEC ||
                    instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                    instruction == icode::opc::ROL || instruction == icode::opc::ROR);
        }
        
        if (mode == "ZEROPAGE_Y") {
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDX ||
                    instruction == icode::opc::STA || instruction == icode::opc::STX ||
                    instruction == icode::opc::CMP || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR);
        }
        
        if (mode == "ABSOLUTE_Y") {
            return (instruction == icode::opc::LDA || instruction == icode::opc::LDX ||
                    instruction == icode::opc::STA || instruction == icode::opc::STX ||
                    instruction == icode::opc::CMP || instruction == icode::opc::ADC ||
                    instruction == icode::opc::SBC || instruction == icode::opc::AND ||
                    instruction == icode::opc::ORA || instruction == icode::opc::EOR);
        }
        if (mode == "ACCUMULATOR") {
            bool isAccumulator = (instruction == icode::opc::ASL || instruction == icode::opc::LSR ||
                                instruction == icode::opc::ROL || instruction == icode::opc::ROR);
            std::cout << "Accumulator check result: " << isAccumulator << "\n";
            return isAccumulator;
      }
        
        std::cout << "Mode '" << mode << "' not recognized or not supported\n";
        return false;
    }
    
    bool procLine(const TextLine &text, Code &code) {
        std::istringstream input(text.text);
        lex::Scanner scan(input);
        std::vector<lex::Token> tokens;
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            if(token.getTokenType() != lex::TOKEN_EOF)
            	tokens.push_back(token);
            
        }
        // for now output each token
        std::cout << "Code Line: ["<<text.index <<"] - [" << text.text << "] = {\n";
        for(unsigned int i = 0; i < tokens.size(); ++i) {
            std::cout << tokens[i] << "\n";
        }
        std::cout << "}\n\n";
        return true;
    }
   
}
