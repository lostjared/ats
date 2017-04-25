#include "code.hpp"

namespace interp {
    
    std::vector<TextLine> lines;
    
    using icode::opc;
    
    iCodeInstruction inst[] = { {opc::ADC, i_adc}, {opc::AND, i_and}, {opc::ASL, i_asl},
        {opc::BCC, i_bcc}, {opc::BCS, i_bcs}, {opc::BEQ, i_beq}, {opc::BIT, i_bit},
        {opc::BMI, i_bmi}, {opc::BNE, i_bne}, {opc::BPL, i_bpl}, {opc::BRK, i_brk},
        {opc::BVC, i_bvc}, {opc::BVS, i_bvs}, {opc::CLC, i_clc}, {opc::CLD, i_cld},
        {opc::CLI, i_cli}, {opc::CLV, i_clv}, {opc::CMP, i_cmp}, {opc::CPX, i_cpx},
        {opc::CPY, i_cpy}, {opc::DEC, i_dec}, {opc::DEX, i_dex}, {opc::DEY, i_dey},
        {opc::EOR, i_eor}, {opc::INC, i_inc}, {opc::INT, i_int}, {opc::INX, i_inx},
        {opc::INY, i_iny}, {opc::JMP, i_jmp}, {opc::JSR, i_jsr}, {opc::LDA, i_lda},
        {opc::LDM, i_ldm}, {opc::LDX, i_ldx}, {opc::LDY, i_ldy}, {opc::LSR, i_lsr},
        {opc::NOP, i_nop}, {opc::ORA, i_ora}, {opc::PEEK, i_peek}, {opc::PHA, i_pha},
        {opc::PHP, i_php}, {opc::PLA, i_pla}, {opc::PLP, i_plp}, {opc::POKE, i_poke},
        {opc::ROL, i_rol}, {opc::ROR, i_ror}, {opc::RTI, i_rti}, {opc::RTS, i_rts},
        {opc::SBC, i_sbc}, {opc::SEC, i_sec}, {opc::SED, i_sed}, {opc::SEI, i_sei},
        {opc::STA, i_sta}, {opc::STX, i_stx}, {opc::STY, i_sty}, {opc::TAX, i_tax},
        {opc::TAY, i_tay}, {opc::TSX, i_tsx}, {opc::TXA, i_txa}, {opc::TXS, i_txs},
        {opc::TYA, i_tya}
    };
    
    void testcodes() {
        for(unsigned int i = 0; icode::op_array[i] != 0; ++i) {
            icode::opc c = static_cast<icode::opc>(i);
            if(inst[i].opcode == c) {
                std::cout << icode::op_array[i] << " correct.\n";
            } else {
                std::cout << icode::op_array[i] << " incorrect.\n";
            }
        }
    }
    
    
    Code::Code() {
        memset(mem, 0, sizeof(mem));
    }
    
    void Code::print() {
        std::cout << "{ ";
        proc.printRegisters();
        proc.printFlags();
        std::cout << "}\n";
    }
    
    
}
