#ifndef __ICODE__H__
#define __ICODE__H__

#include<iostream>
#include<string>

namespace icode {
    
    extern const char *op_array[];
    
    enum class opc { ADC=0, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS, CLC, CLD, CLI, CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR, INC, INT, INX, INY, JMP, JSR, LDA, LDM, LDX, LDY, LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL, ROR, RTI, RTS, SBC, SEC, SED, SEI, STA, STX, STY, TAX, TAY, TSX, TXA, TXS, TYA, NOTINC };
    
    opc strtoInc(const std::string &inc);
    std::string lcase(std::string text);
    
    class Instruction {
        opc opcode;
        
    };
}

#endif
