#include "code.hpp"
#include "icode.hpp"
#include "function.hpp"
#include <sstream>

namespace interp {
    
    bool loadCodeFromString(const std::string &code_string) {
        // Clear existing lines
        if(!lines.empty()) {
            lines.clear();
        }
        
        // Clear existing instructions and labels
        code.instruct.clear();
        if(!label_table.empty()) {
            label_table.clear();
        }
        if(!label_line_table.empty()) {
            label_line_table.clear();
        }
        
        std::istringstream stream(code_string);
        std::string line;
        int line_number = 1;
        
        while(std::getline(stream, line)) {
            // Process each line like your existing file loader
            std::string processed_line = line;
            
            // Remove comments (anything after ';')
            size_t comment_pos = processed_line.find(';');
            if(comment_pos != std::string::npos) {
                processed_line = processed_line.substr(0, comment_pos);
            }
            
            // Trim whitespace
            processed_line.erase(0, processed_line.find_first_not_of(" \t\r\n"));
            processed_line.erase(processed_line.find_last_not_of(" \t\r\n") + 1);
            
            // Skip empty lines
            if(!processed_line.empty()) {
                TextLine text_line;
                text_line.index = line_number;
                text_line.text = processed_line;
                lines.push_back(text_line);
            }
            
            line_number++;
        }
        
        return !lines.empty();
    }
}