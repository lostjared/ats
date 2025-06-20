#ifndef __CODE_HPP__
#define __CODE_HPP__
#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<bitset>
#include "lexer.hpp"
#include "symbol.hpp"
#include "icode.hpp"

namespace interp {

    extern std::ostringstream stream;
    extern std::ostringstream comp_err;
    extern  std::vector<std::pair<uint16_t, uint8_t>> modifiedMemoryAddresses;
    void trackMemoryWrite(uint16_t address, uint8_t value); 
    extern bool mem_write;
    class Runtime_E {
    public:
        Runtime_E(const std::string &t) : text(t) { }
        std::string text;
    };
    
    // address modes
    enum { 
        IMMEDIATE=1, ZEROPAGE, ZEROPAGE_X, ZEROPAGE_Y, 
        ABSOLUTE, ABSOLUTE_X, ABSOLUTE_Y, IMPLIED, RELATIVE, 
        INDIRECT_I,     // (address),Y 
        INDEXED_I,      // (address,X)
        ACCUMULATOR, 
        INDIRECT        // (address) - JMP only
    };
    
    extern const char *add_mode[];
    
    class TextLine {
    public:
        TextLine();
        TextLine(int index, std::string text);
        TextLine(const TextLine &t);
        bool operator<(const TextLine &t) const;
        bool operator==(const TextLine &t1) const;
        bool operator!=(const TextLine &t1) const;
        TextLine &operator=(const TextLine &t);
        int index;
        std::string text;
    };
    
    class Code {
    public:
        Code();
        bool running() const { return run; }
        void start(bool debug=false);
        void step();
        void stop();
        void end();
        void pause();
        void cont();
        void execute(bool debug=false);
        void clear();
        void print();
        void reset();
        void reset_memory();
        void printCurrent();
        uint8_t peek(uint16_t address) const;
        void poke(uint16_t address, uint8_t value);
        void loadFromString(const std::string& code_text);

        symbol::Symbol symbols;
        icode::Processor proc;
        std::vector<uint8_t> stack;
        std::vector<uint32_t> in_stack;
        uint8_t mem[0xFFFF+1];
        std::vector<icode::Instruction> instruct;
    private:
        void procInstruct(icode::Instruction &i);
        bool run;
    };

    typedef void (*call)(Code &c);
    
    struct at_code {
        unsigned char op_code;
        int address_mode;
        icode::opc p_code;
    };
    
    extern at_code m_code[];
    
    struct iCodeInstruction {
        icode::opc opcode;
        call call_back;
        unsigned int mode;
    };
    
    void i_adc(Code &c);
    void i_and(Code &c);
    void i_asl(Code &c);
    void i_bcc(Code &c);
    void i_bcs(Code &c);
    void i_beq(Code &c);
    void i_bit(Code &c);
    void i_bmi(Code &c);
    void i_bne(Code &c);
    void i_bpl(Code &c);
    void i_brk(Code &c);
    void i_bvc(Code &c);
    void i_bvs(Code &c);
    void i_clc(Code &c);
    void i_cld(Code &c);
    void i_cli(Code &c);
    void i_clv(Code &c);
    void i_cmp(Code &c);
    void i_cpx(Code &c);
    void i_cpy(Code &c);
    void i_dec(Code &c);
    void i_dex(Code &c);
    void i_dey(Code &c);
    void i_end(Code &c);
    void i_eor(Code &c);
    void i_inc(Code &c);
    void i_int(Code &c);
    void i_inx(Code &c);
    void i_iny(Code &c);
    void i_jmp(Code &c);
    void i_jsr(Code &c);
    void i_lda(Code &c);
    void i_ldm(Code &c);
    void i_ldx(Code &c);
    void i_ldy(Code &c);
    void i_lsr(Code &c);
    void i_nop(Code &c);
    void i_ora(Code &c);
    void i_pha(Code &c);
    void i_php(Code &c);
    void i_pla(Code &c);
    void i_plp(Code &c);
    void i_rol(Code &c);
    void i_ror(Code &c);
    void i_rti(Code &c);
    void i_rts(Code &c);
    void i_sbc(Code &c);
    void i_sec(Code &c);
    void i_sed(Code &c);
    void i_sei(Code &c);
    void i_sta(Code &c);
    void i_stx(Code &c);
    void i_sty(Code &c);
    void i_tax(Code &c);
    void i_tay(Code &c);
    void i_tsx(Code &c);
    void i_txa(Code &c);
    void i_txs(Code &c);
    void i_tya(Code &c);
    
    extern iCodeInstruction inst[];
    void testcodes();
    extern std::unordered_map<std::string, int> label_table;
    extern std::unordered_map<int, int> label_line_table;
    
    bool inputText(std::vector<lex::Token> &tokens, std::string text);
    bool saveLineSource(const std::string &text);
    bool openLineSource(const std::string &text);
    bool openLineString(const std::string &text);
    bool parseLineSource(const std::string &code_string);
    void insertText(std::vector<lex::Token> &tokens, const TextLine &in);
    bool loadCodeFromString(const std::string &code_string);
    bool procLine(const TextLine &text, Code &code);
    bool checkInstruction(std::vector<lex::Token> &tokens, const TextLine &text);
    bool validateAddressingMode(std::vector<lex::Token> &tokens, icode::opc instruction, unsigned int offset);
    bool validateInstructionAddressingMode(icode::opc instruction, const std::string& mode);
    bool validateInstructionIndirectMode(icode::opc instruction, const std::string& mode);
    bool parseIndirectAddressing(std::vector<lex::Token> &tokens, icode::opc instruction, int startIndex);
    bool validateInstructionAddressingMode(icode::opc instruction, const std::string& mode);
    bool isBranchInstruction(icode::opc op);
    extern std::vector<TextLine> lines;
}

#endif
