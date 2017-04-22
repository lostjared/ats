#include "icode.hpp"
#include<cctype>

namespace icode {
    
    const char *op_array[] = { "adc", "and", "asl", "bcc", "bcs", "beq", "bit", "bmi","bne", "bpl", "brk", "bvc","bvs", "clc", "cld", "cli", "clv", "cmp","cpx","cpy","dec","dex", "dey", "eor", "inc", "int", "inx", "iny", "jmp", "jsr","lda", "ldm","ldx", "ldy","lsr", "nop", "ora","peek", "pha", "php", "pla", "plp", "poke","rol", "ror","rti","rts", "sbc", "sec","sed", "sei", "sta", "stx", "sty", "tax", "tay", "tsx","txa","txs", "tya", 0 };
    
    
    std::string lcase(std::string text) {
        std::string n;
        for(unsigned int i = 0; i < text.size(); ++i) {
            n += tolower(text[i]);
        }
        return n;
    }
    
    opc strtoInc(const std::string &inc) {
        std::string in = lcase(inc);
        for(unsigned int i = 0; op_array[i] != 0; ++i) {
            if(in == op_array[i]) return static_cast<opc>(i);
        }
        return opc::NOTINC;
    }
    
}
