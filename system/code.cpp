#include "code.hpp"

namespace interp {
    
    std::vector<TextLine> lines;
    
    Code::Code() {
        memset(mem, 0, sizeof(mem));
    }
    
    void Code::printFlags() {
        proc.printFlags();
    }
    
}
