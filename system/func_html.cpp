#include "function.hpp"

namespace token {
    void token_HTML(const std::string &command, std::vector<lex::Token> &tokens) {
        if(tokens[1].getTokenType() != lex::TOKEN_STRING) {
            std::cerr << "Error command requires string with filename.\n";
            return;
        }
        if(code.instruct.size()==0) {
            std::cerr << "Error: Must run build command first.\n";
            return;
        }
        std::string fname = tokens[1].getToken();
        std::fstream file;
        file.open(fname, std::ios::out);
        if(!file.is_open()) {
            std::cerr << "Error: file " << fname << " could not be opened for writing.\n";
            return;
        }
        file << "<!DOCTYPE html>\n<html>\n<head><title>ats (Assembly Script) - Debug Information</title></head>\n<body>\n";
        file << "<table border=\"1\" cellpadding=\"3\" cellspacing=\"3\">\n";
        file << "<tr><th>Line</th><th>Address Mode</th><th>Instruction</th><th>Machine Code</th></tr>\n";
        for(unsigned int i = 0; i < code.instruct.size(); ++i) {
            file << "<tr>";
            file << "<th>" << code.instruct[i].line_num << "</th>";
            file << "<th>" << interp::add_mode[code.instruct[i].mode] << "</th>";
            file << "<th>" << code.instruct[i].text << "</th>";
            file << "<th>" << icode::instructionToHex(code.instruct[i]) << "</th>";
            file << "</tr>\n";
        }
        file << "\n</table>\n";
        file << "\n</body>\n</html>\n";
        file.close();
        std::cout << "Wrote HTML debug info to file: " << fname << "\n";
        
    }
}
