#include "code.hpp"
#include "translate.hpp"
#include <bitset>

namespace interp {

    void trackMemoryWrite(uint16_t address, uint8_t value) {
        modifiedMemoryAddresses.push_back(std::make_pair(address, value));
    }

    void updateZNFlags(icode::Processor &proc, uint8_t value) {
        proc.setFlag(icode::FLAG_ZERO, (value == 0));
        proc.setFlag(icode::FLAG_NEGATIVE, ((value & 0x80) != 0));
    }

    void i_adc(Code &c) {
        int in = c.proc.getIp();
        uint8_t carry = c.proc.getFlag(icode::FLAG_CARRY);

        switch (c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                uint8_t val = 0;
                switch (c.instruct.at(in).mode) {
                    case ABSOULTE:
                        val = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        val = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t effective_addr = base_addr + c.proc.reg_y;

                        val = c.peek(effective_addr);
                    }
                    break;
                    case INDEXED_I: { // (address,X)
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t indexed_addr = (zp_addr + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(indexed_addr);
                        uint8_t high = c.peek((indexed_addr + 1) & 0xFF);
                        uint16_t effective_addr = (high << 8) | low;

                        val = c.peek(effective_addr);
                    }
                    break;
                    default:
                        return;
                }
                uint16_t total = c.proc.reg_a + val + carry;
                c.proc.setFlag(icode::FLAG_CARRY, (total > 0xFF));

                bool A7 = (c.proc.reg_a & 0x80);
                bool M7 = (val & 0x80);
                bool R7 = ((static_cast<uint8_t>(total) & 0x80) != 0);
                c.proc.setFlag(icode::FLAG_OVERFLOW, ((A7 == M7) && (A7 != R7)));

                c.proc.reg_a = static_cast<uint8_t>(total & 0xFF);
                updateZNFlags(c.proc, c.proc.reg_a);
            }
            break;

            case icode::op_type::OP_DECIMAL: {
                uint8_t val = c.instruct.at(in).op1.op;
                uint16_t total = c.proc.reg_a + val + carry;
                if (c.proc.getFlag(icode::FLAG_DECIMAL)) {
                    uint8_t lo = (c.proc.reg_a & 0x0F) + (val & 0x0F) + carry;
                    if (lo > 9) lo += 6;
                    uint8_t hi = (c.proc.reg_a >> 4) + (val >> 4) + (lo > 0x0F ? 1 : 0);
                    if (hi > 9) hi += 6;
                    total = (hi << 4) | (lo & 0x0F);
                    c.proc.setFlag(icode::FLAG_CARRY, (hi > 0x0F));
                } else {
                    c.proc.setFlag(icode::FLAG_CARRY, (total > 0xFF));
                }
                bool A7 = (c.proc.reg_a & 0x80);
                bool M7 = (val & 0x80);
                bool R7 = (total & 0x80);
                c.proc.setFlag(icode::FLAG_OVERFLOW, ((A7 == M7) && (A7 != R7)));
                c.proc.reg_a = static_cast<uint8_t>(total & 0xFF);
                updateZNFlags(c.proc, c.proc.reg_a);
            }
            break;

            default:
                break;
        }
    }

    void i_sbc(Code &c) {
        int in = c.proc.getIp();
        uint8_t carry = c.proc.getFlag(icode::FLAG_CARRY);

        switch (c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                uint8_t val = 0;
                switch (c.instruct.at(in).mode) {
                    case ABSOULTE:
                        val = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        val = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t effective_addr = base_addr + c.proc.reg_y;

                        val = c.peek(effective_addr);
                    }
                    break;
                    case INDEXED_I: { // (address,X)
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t indexed_addr = (zp_addr + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(indexed_addr);
                        uint8_t high = c.peek((indexed_addr + 1) & 0xFF);
                        uint16_t effective_addr = (high << 8) | low;

                        val = c.peek(effective_addr);
                    }
                    break;
                    default:
                        return;
                }

                uint16_t total = c.proc.reg_a - val - (1 - carry);
                c.proc.setFlag(icode::FLAG_CARRY, (c.proc.reg_a >= (val + (1 - carry))));

                bool A7 = (c.proc.reg_a & 0x80);
                bool M7 = (val & 0x80);
                bool R7 = (total & 0x80);
                c.proc.setFlag(icode::FLAG_OVERFLOW, ((A7 != M7) && (A7 != R7)));

                c.proc.reg_a = static_cast<uint8_t>(total & 0xFF);
                updateZNFlags(c.proc, c.proc.reg_a);
            }
            break;

            case icode::op_type::OP_DECIMAL: {
                uint8_t val = c.instruct.at(in).op1.op;
                uint16_t total = c.proc.reg_a - val - (1 - carry);
                if (c.proc.getFlag(icode::FLAG_DECIMAL)) {
                    uint8_t lo = (c.proc.reg_a & 0x0F) - (val & 0x0F) - (1 - carry);
                    if (lo & 0x10) lo -= 6;
                    uint8_t hi = (c.proc.reg_a >> 4) - (val >> 4) - ((lo & 0x10) ? 1 : 0);
                    if (hi & 0x10) hi -= 6;
                    total = (hi << 4) | (lo & 0x0F);
                    c.proc.setFlag(icode::FLAG_CARRY, !(hi & 0x10));
                } else {
                    c.proc.setFlag(icode::FLAG_CARRY, (c.proc.reg_a >= (val + (1 - carry))));
                }
                bool A7 = (c.proc.reg_a & 0x80);
                bool M7 = (val & 0x80);
                bool R7 = (total & 0x80);
                c.proc.setFlag(icode::FLAG_OVERFLOW, ((A7 != M7) && (A7 != R7)));
                c.proc.reg_a = static_cast<uint8_t>(total & 0xFF);
                updateZNFlags(c.proc, c.proc.reg_a);
            }
            break;

            default:
                break;
        }
    }

    void i_and(Code &c) {
        int in = c.proc.getIp();
        uint8_t val = 0;
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        val = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        val = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t effective_addr = base_addr + c.proc.reg_y;

                        val = c.peek(effective_addr);
                    }
                    break;
                    case INDEXED_I: { // (address,X)
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t indexed_addr = (zp_addr + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(indexed_addr);
                        uint8_t high = c.peek((indexed_addr + 1) & 0xFF);
                        uint16_t effective_addr = (high << 8) | low;

                        val = c.peek(effective_addr);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            case icode::op_type::OP_DECIMAL: {
                val = c.instruct.at(in).op1.op;
            }
            break;
            default:
                return;
        }
        c.proc.reg_a &= val;
        updateZNFlags(c.proc, c.proc.reg_a);
    }

    void i_asl(Code &c) {
        int in = c.proc.getIp();
        
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_REGISTER_A: { 
                uint8_t oldVal = c.proc.reg_a;  // Declare oldVal here
                
                // Set carry flag to bit 7 of accumulator
                c.proc.setFlag(icode::FLAG_CARRY, (oldVal & 0x80) != 0);
                
                // Shift left
                c.proc.reg_a <<= 1;
                
                // Update Zero and Negative flags
                updateZNFlags(c.proc, c.proc.reg_a);
            } break;
            
            case icode::op_type::OP_MEMORY: {
                uint8_t addr = c.instruct.at(in).op1.op;
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE: {
                        uint8_t cc = c.peek(addr);
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc <<= 1;
                        c.poke(addr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE: {
                        uint8_t realAddr = addr & 0xFF;
                        uint8_t cc = c.peek(realAddr);
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc <<= 1;
                        c.poke(realAddr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ABSOULTE_X: {
                        uint16_t addrX = (addr + c.proc.reg_x) & 0xFFFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc <<= 1;
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addrX = (addr + c.proc.reg_x) & 0xFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc <<= 1;
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            default:
                break;
        }
    }

    void i_bcc(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_CARRY) == 0) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_bcs(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_CARRY) == 1) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_beq(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_ZERO) == 1) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_bit(Code &c) {
        int in = c.proc.getIp();
        
        if (c.instruct.at(in).op1.op_t != icode::op_type::OP_MEMORY) {
            return;
        }   
        uint8_t operand = 0;
        switch (c.instruct.at(in).mode) {
            case interp::ABSOULTE:
            case interp::ZEROPAGE:
                operand = c.peek(c.instruct.at(in).op1.op);
                break;
            default:
                return;
        }
        uint8_t result = c.proc.reg_a & operand;
        c.proc.setFlag(icode::FLAG_ZERO, (result == 0));
        c.proc.setFlag(icode::FLAG_NEGATIVE, ((operand & 0x80) != 0));
        c.proc.setFlag(icode::FLAG_OVERFLOW, ((operand & 0x40) != 0));
    }

    void i_bmi(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_NEGATIVE) == 1) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_bne(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_ZERO) == 0) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_bpl(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_NEGATIVE) == 0) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_brk(Code &c) {
        uint16_t pc_plus_2 = c.proc.ip + 2;
        c.poke(0x0100 + c.proc.sp, (pc_plus_2 >> 8) & 0xFF);
        c.proc.sp--;
        c.poke(0x0100 + c.proc.sp, pc_plus_2 & 0xFF);
        c.proc.sp--;
        uint8_t status = c.proc.valFlags() | 0x10; 
        c.poke(0x0100 + c.proc.sp, status);
        c.proc.sp--;
        
        c.proc.setFlag(icode::FLAG_INTERRUPT, 1);
        c.stop();
        std::cout << "BRK instruction executed\n";
    }

    void i_bvc(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_OVERFLOW) == 0) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_bvs(Code &c) {
        unsigned int ip = c.proc.getIp();
        if(c.proc.getFlag(icode::FLAG_OVERFLOW) == 1) {
            c.proc.ip = c.instruct[ip].op1.label_index - 1;
        }
    }

    void i_clc(Code &c) {
        c.proc.setFlag(icode::FLAG_CARRY, 0);
    }

    void i_cld(Code &c) {
        c.proc.setFlag(icode::FLAG_DECIMAL, 0);
    }

    void i_cli(Code &c) {
        c.proc.setFlag(icode::FLAG_INTERRUPT, 0);
    }

    void i_clv(Code &c) {
        c.proc.setFlag(icode::FLAG_OVERFLOW, 0);
    }

    void i_cmp(Code &c) {
        int in = c.proc.getIp();
        uint8_t operand = 0;
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        operand = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        operand = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        operand = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        operand = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        operand = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        operand = c.peek(addr);
                    }
                    break;
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t effective_addr = base_addr + c.proc.reg_y;

                        operand = c.peek(effective_addr);
                    }
                    break;
                    case INDEXED_I: { // (address,X)
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t indexed_addr = (zp_addr + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(indexed_addr);
                        uint8_t high = c.peek((indexed_addr + 1) & 0xFF);
                        uint16_t effective_addr = (high << 8) | low;

                        operand = c.peek(effective_addr);
                    }
                    break;
                    default:
                        return;
                }
                break;
            case icode::op_type::OP_DECIMAL:
                operand = c.instruct.at(in).op1.op;
                break;
            default:
                return;
        }
        uint8_t result = c.proc.reg_a - operand;
        c.proc.setFlag(icode::FLAG_CARRY, (c.proc.reg_a >= operand));
        updateZNFlags(c.proc, result);
    }

    void i_cpx(Code &c) {
        int in = c.proc.getIp();
        uint8_t operand = 0;
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        operand = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        operand = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    default:
                        return;
                }
                break;
            case icode::op_type::OP_DECIMAL:
                operand = c.instruct.at(in).op1.op;
                break;
            default:
                return;
        }
        uint8_t result = c.proc.reg_x - operand;
        c.proc.setFlag(icode::FLAG_CARRY, (c.proc.reg_x >= operand));
        updateZNFlags(c.proc, result);
    }

    void i_cpy(Code &c) {
        int in = c.proc.getIp();
        uint8_t operand = 0;
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        operand = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        operand = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    default:
                        return;
                }
                break;
            case icode::op_type::OP_DECIMAL:
                operand = c.instruct.at(in).op1.op;
                break;
            default:
                return;
        }
        uint8_t result = c.proc.reg_y - operand;
        c.proc.setFlag(icode::FLAG_CARRY, (c.proc.reg_y >= operand));
        updateZNFlags(c.proc, result);
    }

    void i_dec(Code &c) {
        int in = c.proc.getIp();
        uint8_t addr = c.instruct.at(in).op1.op;
        switch(c.instruct.at(in).mode) {
            case ABSOULTE: {
                uint8_t value = c.peek(addr) - 1;
                c.poke(addr, value);
                updateZNFlags(c.proc, value);
            }
            break;
            case ZEROPAGE: {
                uint8_t realAddr = addr & 0xFF;
                uint8_t value = c.peek(realAddr) - 1;
                c.poke(realAddr, value);
                updateZNFlags(c.proc, value);
            }
            break;
            case ABSOULTE_X: {
                uint16_t addrX = (addr + c.proc.reg_x) & 0xFFFF;  
                uint8_t value = c.peek(addrX) - 1;
                c.poke(addrX, value);
                updateZNFlags(c.proc, value);
            }
            break;
            case ZEROPAGE_X: {
                uint8_t addrX = (addr + c.proc.reg_x) & 0xFF;
                uint8_t value = c.peek(addrX) - 1;
                c.poke(addrX, value);
                updateZNFlags(c.proc, value);
            }
            break;
            default:
                return;
        }
    }

    void i_int(Code &c) {

    }

    void i_inx(Code &c) {
        c.proc.reg_x = c.proc.reg_x + 1;
        updateZNFlags(c.proc, c.proc.reg_x);
    }

    void i_iny(Code &c) {
        c.proc.reg_y = c.proc.reg_y + 1;
        updateZNFlags(c.proc, c.proc.reg_y);
    }

    void i_jmp(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_LABELTEXT:
            case icode::op_type::OP_LABEL:
                c.proc.ip = c.instruct.at(in).op1.label_index - 1;
                return;
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.proc.ip = c.instruct.at(in).op1.op - 1;
                        break;
                    case INDIRECT: { 
                        uint16_t addr = c.instruct.at(in).op1.op;
                        uint8_t low = c.peek(addr);
                        uint8_t high = c.peek(addr + 1);
                        uint16_t target = (high << 8) | low;
                        c.proc.ip = target - 1;
                    }
                    break;
                    default:
                        return;
                }
                break;
            default:
                break;
        }
    }


    void i_jsr(Code &c) {
        int in = c.proc.getIp();
        uint16_t return_addr = c.proc.ip + 1;
        uint8_t orig_sp = c.proc.sp;
        uint8_t high = (return_addr >> 8) & 0xFF;
        c.poke(0x0100 + c.proc.sp, high);
        c.proc.sp = (c.proc.sp - 1) & 0xFF;
        uint8_t low = return_addr & 0xFF;
        c.poke(0x0100 + c.proc.sp, low);
        c.proc.sp = (c.proc.sp - 1) & 0xFF;
        c.proc.ip = c.instruct.at(in).op1.label_index - 1;
    }


    void i_lda(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.proc.reg_a = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        c.proc.reg_a = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        c.proc.reg_a = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        c.proc.reg_a = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        c.proc.reg_a = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        c.proc.reg_a = c.peek(addr);
                    }
                    break;
                    case INDEXED_I: {  // (address,X)
                        uint8_t zp_addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t target_addr = (high << 8) | low;
                        c.proc.reg_a = c.peek(target_addr);
                    }
                    break;
                    
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t target_addr = (base_addr + c.proc.reg_y) & 0xFFFF;
                        c.proc.reg_a = c.peek(target_addr);
                    }
                    break;
                    
                    default:
                        return;
                }
                updateZNFlags(c.proc, c.proc.reg_a);
                break;
            case icode::op_type::OP_DECIMAL:
                c.proc.reg_a = c.instruct.at(in).op1.op;
                updateZNFlags(c.proc, c.proc.reg_a);
                break;
            default:
                break;
        }
    }

    void i_ldm(Code &c) {
        // To be implemented.
    }

    void i_ldx(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.proc.reg_x = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        c.proc.reg_x = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        c.proc.reg_x = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        c.proc.reg_x = c.peek(addr);
                    }
                    break;
                    default:
                        return;
                }
                updateZNFlags(c.proc, c.proc.reg_x);
                break;
            case icode::op_type::OP_DECIMAL:
                c.proc.reg_x = c.instruct.at(in).op1.op;
                updateZNFlags(c.proc, c.proc.reg_x);
                break;
            default:
                break;
        }
    }

    void i_ldy(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.proc.reg_y = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        c.proc.reg_y = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        c.proc.reg_y = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        c.proc.reg_y = c.peek(addr);
                    }
                    break;
                    default:
                        return;
                }
                updateZNFlags(c.proc, c.proc.reg_y);
                break;
            case icode::op_type::OP_DECIMAL:
                c.proc.reg_y = c.instruct.at(in).op1.op;
                updateZNFlags(c.proc, c.proc.reg_y);
                break;
            default:
                break;
        }
    }

    void i_lsr(Code &c) {
        unsigned int ip = c.proc.getIp();
        switch(c.instruct[ip].op1.op_t) {
            case icode::op_type::OP_REGISTER_A: { // ACCUMULATOR mode
                uint8_t oldVal = c.proc.reg_a;  // Declare oldVal here
                
                // Set carry flag to bit 0 of accumulator
                c.proc.setFlag(icode::FLAG_CARRY, (oldVal & 0x01) != 0);
                
                // Shift right
                c.proc.reg_a >>= 1;
                
                // Update Zero and Negative flags
                updateZNFlags(c.proc, c.proc.reg_a);
            } break;
            
            case icode::op_type::OP_MEMORY: {
                uint8_t addr = c.instruct[ip].op1.op;
                switch(c.instruct[ip].mode) {
                    case ABSOULTE: {
                        uint8_t cc = c.peek(addr);
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc >>= 1;
                        c.poke(addr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE: {
                        uint8_t realAddr = addr & 0xFF;
                        uint8_t cc = c.peek(realAddr);
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc >>= 1;
                        c.poke(realAddr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ABSOULTE_X: {
                        uint16_t addrX = (addr + c.proc.reg_x) & 0xFFFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc >>= 1;
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addrX = (addr + c.proc.reg_x) & 0xFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc >>= 1;
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            default:
                break;
        }
    }

    void i_nop(Code &c) {
        std::cout << "nop\n";
    }

    void i_ora(Code &c) {
        int in = c.proc.getIp();
        uint8_t val = 0;
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        val = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        val = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t effective_addr = base_addr + c.proc.reg_y;

                        val = c.peek(effective_addr);
                    }
                    break;
                    case INDEXED_I: { // (address,X)
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t indexed_addr = (zp_addr + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(indexed_addr);
                        uint8_t high = c.peek((indexed_addr + 1) & 0xFF);
                        uint16_t effective_addr = (high << 8) | low;

                        val = c.peek(effective_addr);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            case icode::op_type::OP_DECIMAL: {
                val = c.instruct.at(in).op1.op;
            }
            break;
            default:
                return;
        }
        c.proc.reg_a |= val;
        updateZNFlags(c.proc, c.proc.reg_a);
    }

    void i_eor(Code &c) {
        int in = c.proc.getIp();
        uint8_t val = 0;
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        val = c.peek(c.instruct.at(in).op1.op);
                        break;
                    case ZEROPAGE:
                        val = c.peek(c.instruct.at(in).op1.op & 0xFF);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        val = c.peek(addr);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        val = c.peek(addr);
                    }
                    break;
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t effective_addr = base_addr + c.proc.reg_y;

                        val = c.peek(effective_addr);
                    }
                    break;
                    case INDEXED_I: { // (address,X)
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t indexed_addr = (zp_addr + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(indexed_addr);
                        uint8_t high = c.peek((indexed_addr + 1) & 0xFF);
                        uint16_t effective_addr = (high << 8) | low;

                        val = c.peek(effective_addr);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            case icode::op_type::OP_DECIMAL: {
                val = c.instruct.at(in).op1.op;
            }
            break;
            default:
                return;
        }
        c.proc.reg_a ^= val;
        updateZNFlags(c.proc, c.proc.reg_a);
    }

    void i_inc(Code &c) {
        int in = c.proc.getIp();
        uint8_t addr = c.instruct.at(in).op1.op;
        switch(c.instruct.at(in).mode) {
            case ABSOULTE: {
                uint8_t value = c.peek(addr) + 1;
                c.poke(addr, value);
                updateZNFlags(c.proc, value);
            }
            break;
            case ZEROPAGE: {
                uint8_t realAddr = addr & 0xFF;
                uint8_t value = c.peek(realAddr) + 1;
                c.poke(realAddr, value);
                updateZNFlags(c.proc, value);
            }
            break;
            case ABSOULTE_X: {
                uint16_t addrX = (addr + c.proc.reg_x) & 0xFFFF;  // Add & 0xFFFF
                uint8_t value = c.peek(addrX) + 1;
                c.poke(addrX, value);
                updateZNFlags(c.proc, value);
            }
            break;
            case ZEROPAGE_X: {
                uint8_t addrX = (addr + c.proc.reg_x) & 0xFF;
                uint8_t value = c.peek(addrX) + 1;
                c.poke(addrX, value);
                updateZNFlags(c.proc, value);
            }
            break;
            default:
                return;
        }
    }

    void i_dex(Code &c) {
        c.proc.reg_x = c.proc.reg_x - 1;
        updateZNFlags(c.proc, c.proc.reg_x);
    }

    void i_dey(Code &c) {
        c.proc.reg_y = c.proc.reg_y - 1;
        updateZNFlags(c.proc, c.proc.reg_y);
    }

    void i_end(Code &c) {
        c.stop();
        std::cout << "END instruction executed\n";
    }
    

    
    void i_rts(Code &c) {
        c.proc.sp = (c.proc.sp + 1) & 0xFF;
        uint8_t low = c.peek(0x0100 + c.proc.sp);
        c.proc.sp = (c.proc.sp + 1) & 0xFF;
        uint8_t high = c.peek(0x0100 + c.proc.sp);
        uint16_t addr = ((uint16_t)high << 8) | low;
        c.proc.ip = addr;
    }

    void i_pha(Code &c) {
        c.poke(0x0100 + c.proc.sp, c.proc.reg_a);
        c.proc.sp = (c.proc.sp - 1) & 0xFF;  
    }

    void i_pla(Code &c) {
        c.proc.sp = (c.proc.sp + 1) & 0xFF;
        c.proc.reg_a = c.peek(0x0100 + c.proc.sp);
        updateZNFlags(c.proc, c.proc.reg_a);
    }

    void i_php(Code &c) {
        uint8_t status = c.proc.valFlags() | 0x10; 
        c.poke(0x0100 + c.proc.sp, status);
        c.proc.sp--;
    }

    void i_plp(Code &c) {
        c.proc.sp++;
        uint8_t flags = c.peek(0x0100 + c.proc.sp);
        c.proc.setFlags(flags);
    }

    void i_rti(Code &c) {
        c.proc.sp++;
        uint8_t status = c.peek(0x0100 + c.proc.sp);
        c.proc.sp++;
        uint8_t pcl = c.peek(0x0100 + c.proc.sp);
        c.proc.sp++;
        uint8_t pch = c.peek(0x0100 + c.proc.sp);
        
        c.proc.setFlags(status);
        c.proc.ip = ((uint16_t)pch << 8) | pcl;
    }

    void i_rol(Code &c) {
        int in = c.proc.getIp();
    
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_REGISTER_A: { 
                uint8_t oldVal = c.proc.reg_a;  
                uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                
                // Set carry flag to bit 7 of accumulator
                c.proc.setFlag(icode::FLAG_CARRY, (oldVal & 0x80) != 0);
                
                // Rotate left with old carry
                c.proc.reg_a = (oldVal << 1) | oldCarry;
                
                // Update Zero and Negative flags
                updateZNFlags(c.proc, c.proc.reg_a);
            } break;
            
            case icode::op_type::OP_MEMORY: {
                uint8_t addr = c.instruct.at(in).op1.op;
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE: {
                        uint8_t cc = c.peek(addr);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc = (cc << 1) | oldCarry;
                        c.poke(addr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE: {
                        uint8_t realAddr = addr & 0xFF;
                        uint8_t cc = c.peek(realAddr);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc = (cc << 1) | oldCarry;
                        c.poke(realAddr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ABSOULTE_X: {
                        uint16_t addrX = (addr + c.proc.reg_x) & 0xFFFF;  
                        uint8_t cc = c.peek(addrX);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc = (cc << 1) | oldCarry;
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addrX = (addr + c.proc.reg_x) & 0xFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x80) ? 1 : 0;
                        cc = (cc << 1) | oldCarry;
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            default:
                break;
        }
    }

    void i_ror(Code &c) {
        int in = c.proc.getIp();
    
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_REGISTER_A: { 
                uint8_t oldVal = c.proc.reg_a;  
                uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                c.proc.setFlag(icode::FLAG_CARRY, (oldVal & 0x01) != 0);
                c.proc.reg_a = (oldVal >> 1) | (oldCarry << 7);
                updateZNFlags(c.proc, c.proc.reg_a);
            } break;
            
            case icode::op_type::OP_MEMORY: {
                uint8_t addr = c.instruct.at(in).op1.op;
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE: {
                        uint8_t cc = c.peek(addr);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc = (cc >> 1) | (oldCarry << 7);
                        c.poke(addr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE: {
                        uint8_t realAddr = addr & 0xFF;
                        uint8_t cc = c.peek(realAddr);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc = (cc >> 1) | (oldCarry << 7);
                        c.poke(realAddr, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ABSOULTE_X: {
                        uint16_t addrX = (addr + c.proc.reg_x) & 0xFFFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc = (cc >> 1) | (oldCarry << 7);
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addrX = (addr + c.proc.reg_x) & 0xFF;
                        uint8_t cc = c.peek(addrX);
                        uint8_t oldCarry = c.proc.getFlag(icode::FLAG_CARRY) ? 1 : 0;
                        uint8_t newCarry = (cc & 0x01) ? 1 : 0;
                        cc = (cc >> 1) | (oldCarry << 7);
                        c.poke(addrX, cc);
                        c.proc.setFlag(icode::FLAG_CARRY, newCarry);
                        updateZNFlags(c.proc, cc);
                    }
                    break;
                    default:
                        return;
                }
            }
            break;
            default:
                break;
        }
    }

    void i_sta(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.poke(c.instruct.at(in).op1.op, c.proc.reg_a);
                        ///trackMemoryWrite(c.instruct.at(in).op1.op, c.proc.reg_a);
                        break;
                    case ZEROPAGE:
                        c.poke(c.instruct.at(in).op1.op & 0xFF, c.proc.reg_a);
                        //trackMemoryWrite(c.instruct.at(in).op1.op & 0xFF, c.proc.reg_a);
                        break;
                    case ABSOULTE_X: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFFFF;
                        c.poke(addr, c.proc.reg_a);
                        //trackMemoryWrite(addr, c.proc.reg_a);
                    }
                    break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        //trackMemoryWrite(addr, c.proc.reg_a);
                        c.poke(addr, c.proc.reg_a);
                    }
                    break;
                    case ABSOULTE_Y: {
                        uint16_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFFFF;
                        //trackMemoryWrite(addr, c.proc.reg_a);
                        c.poke(addr, c.proc.reg_a);
                    }
                    break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        //trackMemoryWrite(addr, c.proc.reg_a);
                        c.poke(addr, c.proc.reg_a);
                    }
                    break;
                    case INDEXED_I: {  // (address,X)
                        uint8_t zp_addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t target_addr = (high << 8) | low;
                        c.poke(target_addr, c.proc.reg_a);
                    }
                    break;
                    
                    case INDIRECT_I: { // (address),Y
                        uint8_t zp_addr = c.instruct.at(in).op1.op & 0xFF;
                        uint8_t low = c.peek(zp_addr);
                        uint8_t high = c.peek((zp_addr + 1) & 0xFF);
                        uint16_t base_addr = (high << 8) | low;
                        uint16_t target_addr = (base_addr + c.proc.reg_y) & 0xFFFF;
                        c.poke(target_addr, c.proc.reg_a);
                    }
                    break;
                    
                    default:
                        return;
                }
                break;
            default:
                break;
        }
    }

    void i_stx(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.poke(c.instruct.at(in).op1.op, c.proc.reg_x);
                        break;
                    case ZEROPAGE:
                        c.poke(c.instruct.at(in).op1.op & 0xFF, c.proc.reg_x);
                        break;
                    case ZEROPAGE_Y: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_y) & 0xFF;
                        c.poke(addr, c.proc.reg_x);
                    }
                    break;
                    default:
                        return;
                }
                break;
            default:
                break;
        }
    }

    void i_sty(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct.at(in).op1.op_t) {
            case icode::op_type::OP_MEMORY:
                switch(c.instruct.at(in).mode) {
                    case ABSOULTE:
                        c.poke(c.instruct.at(in).op1.op, c.proc.reg_y);
                        break;
                    case ZEROPAGE:
                        c.poke(c.instruct.at(in).op1.op & 0xFF, c.proc.reg_y);
                        break;
                    case ZEROPAGE_X: {
                        uint8_t addr = (c.instruct.at(in).op1.op + c.proc.reg_x) & 0xFF;
                        c.poke(addr, c.proc.reg_y);
                    }
                    break;
                    default:
                        return;
                }
                break;
            default:
                break;
        }
    }

    void i_tax(Code &c) {
        c.proc.reg_x = c.proc.reg_a;
        updateZNFlags(c.proc, c.proc.reg_x);
    }

    void i_tay(Code &c) {
        c.proc.reg_y = c.proc.reg_a;
        updateZNFlags(c.proc, c.proc.reg_y);
    }

    void i_tsx(Code &c) {
        c.proc.reg_x = c.proc.sp;
        updateZNFlags(c.proc, c.proc.reg_x);
    }

    void i_txa(Code &c) {
        c.proc.reg_a = c.proc.reg_x;
        updateZNFlags(c.proc, c.proc.reg_a);
    }

    void i_txs(Code &c) {
        c.proc.sp = c.proc.reg_x; 
    }

    void i_tya(Code &c) {
        c.proc.reg_a = c.proc.reg_y;
        updateZNFlags(c.proc, c.proc.reg_a);
    }
    
    void i_sec(Code &c) {
        c.proc.setFlag(icode::FLAG_CARRY, 1);
    }

    void i_sed(Code &c) {
        c.proc.setFlag(icode::FLAG_DECIMAL, 1);
    }

    void i_sei(Code &c) {
        c.proc.setFlag(icode::FLAG_INTERRUPT, 1);
    }

}