#include "code.hpp"

namespace interp {
    
    std::vector<TextLine> lines;
    
    Code::Code() {
        memset(mem, 0, sizeof(mem));
    }
    
    void Code::print() {
        std::cout << "{ ";
        proc.printRegisters();
        proc.printFlags();
        std::cout << "}\n";
    }
    
}
