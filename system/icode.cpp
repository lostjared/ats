#include "code.hpp"
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
    
    Operand::Operand(const Operand &o) :op(o.op), op_t(o.op_t), label_text(o.label_text) {}
    
    Operand &Operand::operator=(const Operand &o) {
        op = o.op;
        op_t = o.op_t;
        label_text = o.label_text;
        return *this;
    }
    
    Instruction::Instruction() : opcode(opc::NOTINC) {
        line_num = 0;
        label = false;
        
    }
    
    Instruction::Instruction(unsigned int iline, const opc &op_code, unsigned int m, const Operand &i_op1, const Operand &i_op2) : line_num(iline), opcode(op_code), mode(m), op1(i_op1), op2(i_op2) {}
    
    Instruction::Instruction(const Instruction &i) : op_byte(i.op_byte), line_num(i.line_num), opcode(i.opcode),
    op1(i.op1), op2(i.op2), mode(i.mode), label(i.label), label_text(i.label_text)
    
    {
    }
    
    Instruction &Instruction::operator=(const Instruction &i) {
        opcode = i.opcode;
        op1 = i.op1;
        op2 = i.op2;
        line_num = i.line_num;
        label_text = i.label_text;
        op_byte = i.op_byte;
        mode = i.mode;
        label = i.label;
        return *this;
    }
    
    void Instruction::set(unsigned int iline, const opc &c, unsigned int m, const Operand &o1, const Operand &o2) {
        opcode = c;
        op1 = o1;
        op2 = o2;
        mode = m;
        line_num = iline;
    }
    
    std::string instructionToHex(Instruction &i) {
        if(i.mode <= 0 ||i.mode > interp::INDIRECT) {
            return "invalid address mode";
        }
        std::ostringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(i.op_byte);
        switch(i.op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                
                if(i.mode != interp::ZEROPAGE)
                stream << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i.op1.op;
                else
                    stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << i.op1.op;
            }
                break;
            case icode::op_type::OP_DECIMAL:
                stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << i.op1.op;
                break;
            case icode::op_type::OP_REGISTER:
                break;
            case icode::op_type::OP_LABEL:
                stream << std::setfill('0') << std::setw(2) << i.op1.op;
                break;
            case icode::op_type::OP_LABELTEXT:
                //out << "Branch Label: " << i.op1.label_text << " "; // calculate label
                break;
            default:
                break;
        }
        return stream.str();
    }
    
    std::ostream &operator<<(std::ostream &out, Instruction &i) {
        
        std::ostringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(i.op_byte);
        
        
        if(i.mode <= 0 ||i.mode > interp::INDIRECT) {
            out << "address mode unknown value: " << i.mode << "..\n";
            return out;
        }
        out << "Line: " << std::dec << i.line_num << " Address Mode: " << interp::add_mode[i.mode] << "  Opcode: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(i.op_byte) << " ";
        switch(i.op1.op_t) {
            case icode::op_type::OP_MEMORY:
                if(i.mode != interp::ZEROPAGE) {
                	out << "Operand 1 [Memory Address]: " << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i.op1.op << " ";
                	stream << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << i.op1.op;
                } else {
                    out << "Operand 1 [Zero Page Memory Address]: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << i.op1.op << " ";
                    stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << i.op1.op;
                }
                break;
            case icode::op_type::OP_DECIMAL:
                out << "Operand 1 [Byte Constant]: " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << i.op1.op << " ";
                stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << i.op1.op;
                break;
            case icode::op_type::OP_REGISTER:
                out << "Operand 1 [Register]: "; // register here
                break;
            case icode::op_type::OP_LABEL:
                out << "Branch value: " << std::setfill('0') << std::setw(2) << i.op1.op << " ";
                stream << std::setfill('0') << std::setw(2) << i.op1.op;
                break;
            case icode::op_type::OP_LABELTEXT:
                out << "Branch Label: " << i.op1.label_text << " ";
                break;
            default:
                break;
        }
        // output operand 2
        std::cout << "\nHex for Machine code: " << stream.str() << "\n";
        
        
        return out;
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
