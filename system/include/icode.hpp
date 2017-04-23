#ifndef __ICODE__H__
#define __ICODE__H__

#include<iostream>
#include<string>
#include<cstdint>
#include<bitset>

namespace icode {
    
    extern const char *op_array[];
    
    enum class opc { ADC=0, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS, CLC, CLD, CLI, CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR, INC, INT, INX, INY, JMP, JSR, LDA, LDM, LDX, LDY, LSR, NOP, ORA, PEEK, PHA, PHP, PLA, PLP,POKE,ROL, ROR, RTI, RTS, SBC, SEC, SED, SEI, STA, STX, STY, TAX, TAY, TSX, TXA, TXS, TYA, NOTINC };
    
    opc strtoInc(const std::string &inc);
    std::string lcase(std::string text);
    
    enum class op_type { NULL_TYPE=0, OP_MEMORY, OP_DECIMAL, OP_REGISTER };
    
    class Operand {
    public:
        uint32_t op;
        op_type  op_t;
        Operand();
        Operand(const uint32_t operand, const op_type operand_type);
        Operand(const Operand &o);
        Operand &operator=(const Operand &o);
    };
    
    class Instruction {
    public:
        opc opcode;
        Operand op1, op2;
        Instruction();
        Instruction(const opc op_code, const Operand i_op1, const Operand i_op2);
        Instruction(const Instruction &i);
        Instruction &operator=(const Instruction &i);
        void set(const opc c, const Operand o1, const Operand o2);
        
    };
    
    enum proc_Flags { FLAG_CARRY=0, FLAG_ZERO, FLAG_INTERRUPT, FLAG_DECIMAL, FLAG_BREAK, FLAG_EXPANSION, FLAG_OVERFLOW, FLAG_NEGATIVE };
    
    class Processor {
        std::bitset<8> flags;
        /* 
         C = 0 - carry bit
         Z = 1 - zero bit
         I = 2 - interrupt disable bit
         D = 3 - decimal mode bit
         B = 4 - break command bit
         5 = [expansion bit [not used]
         Z = 6 - overflow bit
         N = 7 - negative bit
        */
        unsigned int ip;
    public:
        Processor();
        
        void setFlag(proc_Flags flag, unsigned int set);
        unsigned int getFlag(proc_Flags flag);
        void clrFlags();
        uint8_t valFlags();
        void reset();
        void setIp(const unsigned int ip_val);
        uint8_t reg_x, reg_y, reg_a;
        void printFlags();
    };
}

#endif
