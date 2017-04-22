#include "code.hpp"

namespace interp {
    
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
    
    bool openLineSource(const std::string &text) {
        std::fstream file;
        file.open(text, std::ios::in);
        if(!file.is_open()) return false;
        if(!lines.empty()) {
            lines.erase(lines.begin(), lines.end());
        }
        while(!file.eof() && file) {
            std::string in;
            std::getline(file,in);
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
            inputText(tokens, in);
        }
        file.close();
        return true;
    }
    
    void insertText(std::vector<lex::Token> &tokens, const TextLine &in) {
        for(unsigned int i = 0; i < lines.size(); ++i) {
            if(lines[i].index == in.index) {
                if(checkInstruction(tokens, in)) {
                	lines[i].text = in.text;
                	return;
                } else return;
            }
        }
        if(checkInstruction(tokens, in)) {
        	lines.push_back(in);
        	std::sort(lines.begin(), lines.end());
        }
    }
    
    void inputText(std::vector<lex::Token> &tokens, std::string input_line) {
        if(tokens.size()>=2 && input_line.length()>0) {
            lex::Token_type num = tokens[0].getTokenType();
            if(num != lex::TOKEN_DIGIT) {
                std::cerr << "Requires line number before code.\n";
                return;
            }
            int value = atoi(tokens[0].getToken().c_str());
            std::string codetext;
            codetext = input_line.substr(input_line.find(tokens[0].getToken())+tokens[0].getToken().length()+1, input_line.length());
            TextLine in(value, codetext);
            insertText(tokens, in);
        } else {
            std::cerr << "Error invalid input.\n";
            return;
        }
    }
    
    bool checkInstruction(std::vector<lex::Token> &tokens, const TextLine &text) {
        if(tokens.size()<= 1) {
            std::cerr << "Error: Statement requires instruction.\n";
            return false;
        }
        if(tokens.size()>=2) {
            icode::opc op = icode::strtoInc(tokens[1].getToken());
            if(op == icode::opc::NOTINC) {
                std::cerr << "Error: " << tokens[1].getToken() << " not a valid instruction..\n";
                return false;
            } else {
                // check operands
                if(tokens.size()>=3) {
                    if(tokens[2].getToken()=="#") {
                        if(tokens.size()>=4) {
                            if(tokens[3].getTokenType() == lex::TOKEN_DIGIT) {}
                            else if(tokens[3].getTokenType() != lex::TOKEN_DIGIT && tokens[3].getTokenType() != lex::TOKEN_HEX) {
                                std::cerr << "Syntax Error: requires either digit or $.\n";
                                return false;
                                
                            } else if(tokens[3].getTokenType() != lex::TOKEN_HEX) {
                                std::cerr << "Syntax Error: $ is followed by a Hex value\n";
                                return false;
                            }
                            
                            if(tokens.size()>=5 && tokens[4].getToken() == ",") {
                                if(tokens.size()>=6 && tokens[5].getTokenType() == lex::TOKEN_CHAR) {
                                    // check if register
                                }
                            }
                            
                        } else {
                            std::cerr << "Syntax Error: Missing value after #\n";
                            return false;
                        }
                    }
                } else {
                    std::cerr << "Syntax Error: Instruction requires operand\n";
                }
            
            }
        }
        return true;
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
