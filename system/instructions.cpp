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
        
    }
    
    void i_ldm(Code &c) {
        
    }
    void i_ldx(Code &c) {
        
    }
    
    void i_ldy(Code &c) {
        
    }
    
    void i_lsr(Code &c) {
        
    }
    
    void i_nop(Code &c) {
        
    }
    
    void i_ora(Code &c) {
        
    }
    
    void i_peek(Code &c) {
        
    }
    
    void i_pha(Code &c) {
        
    }
    
    void i_php(Code &c) {
        
    }
    
    void i_pla(Code &c) {
        
    }
    
    void i_plp(Code &c) {
        
    }
    
    void i_poke(Code &c) {
        
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
        
    }
    
    void i_stx(Code &c) {
        
    }
    
    void i_sty(Code &c) {
        
    }
    
    void i_tax(Code &c) {
        c.proc.reg_x = c.proc.reg_a;
    }
    
    void i_tay(Code &c) {
        c.proc.reg_y = c.proc.reg_a;
        
    }
    void i_tsx(Code &c) {
        c.proc.reg_x = c.proc.sp;
    }
    
    void i_txs(Code &c) {
        c.proc.sp = c.proc.reg_x;
    }
    
    void i_txa(Code &c) {
        c.proc.reg_a = c.proc.reg_x;
    }
    
    void i_tya(Code &c) {
        c.proc.reg_a = c.proc.reg_y;
    }
    
}