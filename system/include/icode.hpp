#ifndef __ICODE__H__
#define __ICODE__H__

#include<iostream>
#include<string>
#include<cstdint>

namespace icode {
    
    extern const char *op_array[];
    
    enum class opc { ADC=0, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS, CLC, CLD, CLI, CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR, INC, INT, INX, INY, JMP, JSR, LDA, LDM, LDX, LDY, LSR, NOP, ORA, PEEK, PHA, PHP, PLA, PLP,POKE,ROL, ROR, RTI, RTS, SBC, SEC, SED, SEI, STA, STX, STY, TAX, TAY, TSX, TXA, TXS, TYA, NOTINC };
    
    opc strtoInc(const std::string &inc);
    std::string lcase(std::string text);
    
    class Instruction {
        opc opcode;
        unsigned int op1, op2;
    };
    
    class Processor {
        bool flags[8];
        /* 
         0 - carry bit
         1 - zero bit
         2 - interrupt disable bit
         3 - decimal mode bit
         4 - break command bit
         5 - expansion bit
         6 - overflow bit
         7 - negative bit
        */
        
    public:
        Processor();
        
        void setFlag(uint8_t flag, bool set);
        bool getFlag(uint8_t flag);
        void clrFlags();
        void reset();
        
        uint8_t reg_x, reg_y, reg_a;
    };
}

#endif
