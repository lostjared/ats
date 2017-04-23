#include "icode.hpp"
#include<cctype>

namespace icode {
    
    const char *op_array[] = { "adc", "and", "asl", "bcc", "bcs", "beq", "bit", "bmi","bne", "bpl", "brk", "bvc","bvs", "clc", "cld", "cli", "clv", "cmp","cpx","cpy","dec","dex", "dey", "eor", "inc", "int", "inx", "iny", "jmp", "jsr","lda", "ldm","ldx", "ldy","lsr", "nop", "ora","peek", "pha", "php", "pla", "plp", "poke","rol", "ror","rti","rts", "sbc", "sec","sed", "sei", "sta", "stx", "sty", "tax", "tay", "tsx","txa","txs", "tya", 0 };
    
    
    Instruction::Instruction() : opcode(opc::NOTINC), op1(0), op2(0),op1_t(op_type::NULL_TYPE), op2_t(op_type::NULL_TYPE)  {}
    
    Instruction::Instruction(opc op_code, op_type op1_type, uint32_t op1_val, op_type op2_type, uint32_t op2_val) : opcode(op_code), op1(op1_val), op2(op2_val), op1_t(op1_type), op2_t(op2_type) {}
    
    Instruction::Instruction(const Instruction &i) : opcode(i.opcode), op1(i.op1), op2(i.op2), op1_t(i.op1_t), op2_t(i.op2_t) {}
    
    Instruction &Instruction::operator=(const Instruction &i) {
        opcode = i.opcode;
        op1 = i.op1;
        op2 = i.op2;
        op1_t = i.op1_t;
        op2_t = i.op2_t;
        return *this;
    }
    
    
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
    
    Processor::Processor() {
        reset();
    }
    
    void Processor::setFlag(proc_Flags flag, bool set) {
        flags[flag] = set;
    }
    
    bool Processor::getFlag(proc_Flags flag) {
        return (flags[flag] == 1);
    }
    
    void Processor::clrFlags() {
        for(uint8_t i = 0; i < 8; ++i)
            setFlag(proc_Flags(i), false);
        
    }
    
    uint8_t Processor::valFlags() {
        return static_cast<uint8_t>(flags.to_ulong());
    }
    
    void Processor::reset() {
        for(uint8_t i = 0; i < 8; ++i)
            setFlag(proc_Flags(i), false);
        
        reg_x = reg_y = reg_a = 0;
        ip = 0;
    }
    
    void Processor::setIp(const unsigned int ip_val) {
        ip = ip_val;
    }
}
