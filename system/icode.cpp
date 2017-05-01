#include "icode.hpp"
#include<cctype>

namespace icode {
    
    const char *op_array[] = { "adc", "and", "asl", "bcc", "bcs", "beq", "bit", "bmi","bne", "bpl", "brk", "bvc","bvs", "clc", "cld", "cli", "clv", "cmp","cpx","cpy","dec","dex", "dey", "eor", "inc", "int", "inx", "iny", "jmp", "jsr","lda", "ldm","ldx", "ldy","lsr", "nop", "ora", "pha", "php", "pla", "plp", "rol", "ror","rti","rts", "sbc", "sec","sed", "sei", "sta", "stx", "sty", "tax", "tay", "tsx","txa","txs", "tya", 0 };
    
    std::ostream &operator<<(std::ostream &out, opc c) {
        if(c != opc::NOTINC)
            out << op_array[static_cast<unsigned int>(c)];
        return out;
    }
    
    
    Operand::Operand() : op(0), op_t(op_type::NULL_TYPE) {}
    
    Operand::Operand(const uint32_t &operand, const op_type &operand_type) : op(operand), op_t(operand_type) {}
    
    Operand::Operand(const Operand &o) :op(o.op), op_t(o.op_t) {}
    
    Operand &Operand::operator=(const Operand &o) {
        op = o.op;
        op_t = o.op_t;
        return *this;
    }
    
    Instruction::Instruction() : opcode(opc::NOTINC) {
        line_num = 0;
        label = false;
        
    }
    
    Instruction::Instruction(unsigned int iline, const opc &op_code, address_mode m, const Operand &i_op1, const Operand &i_op2) : line_num(iline), opcode(op_code), mode(m), op1(i_op1), op2(i_op2) {}
    
    Instruction::Instruction(const Instruction &i) : opcode(i.opcode), op1(i.op1), op2(i.op2) {}
    
    Instruction &Instruction::operator=(const Instruction &i) {
        opcode = i.opcode;
        op1 = i.op1;
        op2 = i.op2;
        return *this;
    }
    
    void Instruction::set(unsigned int iline, const opc &c, address_mode m, const Operand &o1, const Operand &o2) {
        opcode = c;
        op1 = o1;
        op2 = o2;
        mode = m;
        line_num = iline;
    }
    
    std::string lcase(const std::string &text) {
        std::string n;
        for(unsigned int i = 0; i < text.size(); ++i) {
            n += tolower(text[i]);
        }
        return n;
    }
    
    uint32_t toHex(const std::string &text) {
        std::istringstream stream(text);
        uint32_t val = 0;
        stream >> std::hex >> val;
        return val;
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
    
    void Processor::setFlag(proc_Flags flag, unsigned int set) {
        flags[flag] = set;
    }
    
    void Processor::setFlags(uint8_t b) {
        flags = b;
    }
    
    unsigned int Processor::getFlag(proc_Flags flag) {
        return (flags[flag] == 1);
    }
    
    void Processor::clrFlags() {
        for(uint8_t i = 0; i < 8; ++i)
            setFlag(proc_Flags(i), 0);
        
    }
    
    uint8_t Processor::valFlags() {
        return static_cast<uint8_t>(flags.to_ulong());
    }
    
    void Processor::reset() {
        for(uint8_t i = 0; i < 8; ++i)
            setFlag(proc_Flags(i), 0);
        
        reg_x = reg_y = reg_a = 0;
        ip = 0;
        sp = 0;
    }
    
    void Processor::setIp(const address_size &ip_val) {
        ip = ip_val;
    }
    
    address_size Processor::getIp() const { return ip; }
    
    void Processor::printFlags() {
        std::cout << "C:" << getFlag(FLAG_CARRY) << " Z:" << getFlag(FLAG_ZERO) << " I:" << getFlag(FLAG_INTERRUPT) << " D:" << getFlag(FLAG_DECIMAL) << " B:" << getFlag(FLAG_BREAK) << " E:" << getFlag(FLAG_EXPANSION) << " Z:" << getFlag(FLAG_OVERFLOW) << " N:" << getFlag(FLAG_NEGATIVE) << " ";
    }
    
    void Processor::printRegisters() {
        std::cout << "[ X:" << std::hex << std::uppercase << static_cast<int>(reg_x) << " Y:" << std::hex << std::uppercase <<  static_cast<int>(reg_y) << " A:" << std::hex << std::uppercase << static_cast<int>(reg_a) << " P:" << std::hex << std::uppercase << static_cast<int>(valFlags()) << " ] ";
    }
}
