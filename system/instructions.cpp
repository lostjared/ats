#include "code.hpp"

namespace interp {
    
    void i_adc(Code &c) {
        
    }
    
    void i_and(Code &c) {
        
    }
    
    void i_asl(Code &c) {
        
    }
    
    void i_bcc(Code &c) {
        
    }
    
    void i_bcs(Code &c) {
        
    }
    
    void i_beq(Code &c) {
        
    }
    
    void i_bit(Code &c) {
        
    }
    
    void i_bmi(Code &c) {
        
    }
    
    void i_bne(Code &c) {
        
    }
    
    void i_bpl(Code &c) {
        
    }
    
    void i_brk(Code &c) {
        c.pause();
    }
    
    void i_bvc(Code &c) {
        
    }
    
    void i_bvs(Code &c) {
        
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
        
    }
    
    void i_cpx(Code &c) {
        
    }
    
    void i_cpy(Code &c) {
        
    }
    
    void i_dec(Code &c) {
        
    }
    
    void i_dex(Code &c) {
        
    }
    
    void i_dey(Code &c) {
        
    }
    
    void i_eor(Code &c) {
        
    }
    
    void i_inc(Code &c) {
        
    }
    
    void i_int(Code &c) {
        
    }
    
    void i_inx(Code &c) {
        
    }
    
    void i_iny(Code &c) {
        
    }
    
    void i_jmp(Code &c) {
        
    }
    
    void i_jsr(Code &c) {
        
    }
    
    void i_lda(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct[in].op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                switch(c.instruct[in].mode) {
                    case interp::ABSOULTE:
                    case interp::ZEROPAGE:
                        c.proc.reg_a = c.peek(c.instruct[in].op1.op);
                        if(c.proc.reg_a == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    case interp::ABSOULTE_X:
                    case interp::ZEROPAGE_X:
                        c.proc.reg_a = c.peek(c.instruct[in].op1.op+c.proc.reg_x);
                        if(c.proc.reg_a == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    case interp::ABSOULTE_Y:
                    case interp::ZEROPAGE_Y:
                        c.proc.reg_a = c.peek(c.instruct[in].op1.op+c.proc.reg_y);
                        if(c.proc.reg_a == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    default:
                        return;
                }
            }
                break;
            case icode::op_type::OP_DECIMAL:
                c.proc.reg_a = c.instruct[in].op1.op;
                if(c.proc.reg_a == 0)
                    c.proc.setFlag(icode::FLAG_ZERO, 1);
                else
                    c.proc.setFlag(icode::FLAG_ZERO, 0);
                break;
            default:
                break;
        }
    }
    
    void i_ldm(Code &c) {
        
    }
    void i_ldx(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct[in].op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                switch(c.instruct[in].mode) {
                    case interp::ABSOULTE:
                    case interp::ZEROPAGE:
                        c.proc.reg_x = c.peek(c.instruct[in].op1.op);
                        if(c.proc.reg_x == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    case interp::ABSOULTE_Y:
                    case interp::ZEROPAGE_Y:
                        c.proc.reg_x = c.peek(c.instruct[in].op1.op+c.proc.reg_y);
                        if(c.proc.reg_x == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    default:
                        return;
                }
            }
                break;
            case icode::op_type::OP_DECIMAL:
                c.proc.reg_x = c.instruct[in].op1.op;
                if(c.proc.reg_x == 0)
                    c.proc.setFlag(icode::FLAG_ZERO, 1);
                else
                    c.proc.setFlag(icode::FLAG_ZERO, 0);
                
                break;
            default:
                break;
        }
    }
    
    void i_ldy(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct[in].op1.op_t) {
            case icode::op_type::OP_MEMORY: {
                switch(c.instruct[in].mode) {
                    case interp::ABSOULTE:
                    case interp::ZEROPAGE:
                        c.proc.reg_y = c.peek(c.instruct[in].op1.op);
                        if(c.proc.reg_y == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    case interp::ABSOULTE_X:
                    case interp::ZEROPAGE_X:
                        c.proc.reg_y = c.peek(c.instruct[in].op1.op+c.proc.reg_x);
                        if(c.proc.reg_y == 0)
                            c.proc.setFlag(icode::FLAG_ZERO, 1);
                        else
                            c.proc.setFlag(icode::FLAG_ZERO, 0);
                        break;
                    default:
                        return;
                }
            }
                break;
            case icode::op_type::OP_DECIMAL:
                c.proc.reg_y = c.instruct[in].op1.op;
                if(c.proc.reg_y == 0)
                    c.proc.setFlag(icode::FLAG_ZERO, 1);
                else
                    c.proc.setFlag(icode::FLAG_ZERO, 0);
                break;
            default:
                break;
        }
    }
    
    void i_lsr(Code &c) {
        
    }
    
    void i_nop(Code &c) {
        
    }
    
    void i_ora(Code &c) {
        
    }
    
    void i_pha(Code &c) {
        
    }
    
    void i_php(Code &c) {
        
    }
    
    void i_pla(Code &c) {
        
    }
    
    void i_plp(Code &c) {
        
    }
    
    void i_rol(Code &c) {
        
    }
    
    void i_ror(Code &c) {
        
    }
    
    void i_rti(Code &c) {
        
    }
    
    void i_rts(Code &c) {
        
    }
    
    void i_sbc(Code &c) {
        
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
    
    void i_sta(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct[in].op1.op_t) {
            case icode::op_type::OP_MEMORY:
                c.mem[c.instruct[in].op1.op] = c.proc.reg_a;
                break;
            default:
                break;
        }
    }
    
    void i_stx(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct[in].op1.op_t) {
            case icode::op_type::OP_MEMORY:
                c.mem[c.instruct[in].op1.op] = c.proc.reg_x;
                break;
            default:
                break;
        }
    }
    
    void i_sty(Code &c) {
        int in = c.proc.getIp();
        switch(c.instruct[in].op1.op_t) {
            case icode::op_type::OP_MEMORY:
                c.mem[c.instruct[in].op1.op] = c.proc.reg_y;
                break;
            default:
                break;
        }
    }
    
    void i_tax(Code &c) {
        c.proc.reg_x = c.proc.reg_a;
        if(c.proc.reg_x == 0)
            c.proc.setFlag(icode::FLAG_ZERO, 1);
        else
            c.proc.setFlag(icode::FLAG_ZERO, 0);
    }
    
    void i_tay(Code &c) {
        c.proc.reg_y = c.proc.reg_a;
        if(c.proc.reg_y == 0)
            c.proc.setFlag(icode::FLAG_ZERO, 1);
        else
            c.proc.setFlag(icode::FLAG_ZERO, 0);
    }
    void i_tsx(Code &c) {
        c.proc.reg_x = c.proc.sp;
        if(c.proc.reg_x == 0)
            c.proc.setFlag(icode::FLAG_ZERO, 1);
        else
            c.proc.setFlag(icode::FLAG_ZERO, 0);
    }
    
    void i_txs(Code &c) {
        c.proc.sp = c.proc.reg_x;
    }
    
    void i_txa(Code &c) {
        c.proc.reg_a = c.proc.reg_x;
    }
    
    void i_tya(Code &c) {
        c.proc.reg_a = c.proc.reg_y;
        if(c.proc.reg_a == 0)
            c.proc.setFlag(icode::FLAG_ZERO, 1);
        else
            c.proc.setFlag(icode::FLAG_ZERO, 0);
    }
    
}
