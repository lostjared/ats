# ats

Work in progress. In early stages still, but the goal of this project is to teach myself more about interpreters.
This program just plays around with a few different concepts, but borrows a lot of the instructions and concepts from the book "the Atari Assembler".

to build:

$ ./autogen.sh

$ mkdir build

$ cd build

$ ../configure --enable-debug

$ make 


This project is based on 6502 Instructions 
with added functionality and new instructions / features to
allow this old code to be used on modern computers. Emulation of original hardware is not the goal of this project.

Registers: 

	X
	Y
	Accumulator

Base instruction set:

PEEK / POKE

	The Processor Flags

         C = Bit 0 - carry bit
         Z = Bit 1 - zero bit
         I = Bit 2 - interrupt disable bit
         D = Bit 3 - decimal mode bit
         B = Bit 4 - break command bit
         5 = Bit 5 -[expansion bit [not used]
         Z = Bit 6 - overflow bit
         N = Bit 7 - negative bit
        
Instructions:

	ADC - Add Memory to Accumulator with Carry
	AND - And Memory to Accumulator with Carry
	ASL - Shift Left One Bit (memory or accumulator)
	BCC - Branch if Carry Flag is clear
	BCS - Branch if Carry Flag is set
	BEQ - Branch on result Zero
	BIT - Test bits in accumulator with memory
	BMI - Branch on result minus
	BNE - Branch if result not zero
	BPL - Branch on result plus
	BRK - Unconditional break
	BVC - Branch on overflow clear
	BVS - Branch on overflow set
	CLC - Clear Carry Flag
	CLD - Clear Decimal Flag
	CLI - Clear Interupt Flag
	CLV - Clear overflow Flag
	CMP - Compare memory and accumulator
	CPX - Compare Memory and Register X
	CPY - Compare Memory and Reigster Y
	DEC - Decrement Memory or accumulator
	DEX - Decrement X Register
	DEY - Decrement Y Register
	EOR - Exculsive Or memory or accumulator
	INC - Incrmeent Memory or accumulator
	INX - Increment register X
	INY - Increment register Y
	JMP - Unconditonal Jump to Code label or address
	JSR - Jump To Subroutine
	LDA - Load accumulator with constant or memory
	LDX - Load X register with constant or memory
	LDY - Load Y register with constant or memory
	LSR - Shift right one bit
	NOP - No operation 
	ORA - Or accumulator with constant or memory
	PHA - Push accumulator onto the stack
	PHP - Push proccesscor flags onto the stack
	PLA - Pull (pop) accumulator from the stack
	PLP - Pull (pop) proccesscor flags from the stack
	ROL - Rotate bits one left
	ROR - Rotate bits one right
	RTI - Return from interupt
	RTS - Return from subroutine
	SBC - Subtract memory and borrow from accum
	SEC - Set carry flag
	SED - Set decimal flag
	SEI - Set interupt flag
	STA - Store accumulator in memory
	STX - Store register X in memory
	STY - Store register Y in memory
	TAX - Transfer accumulator to X register
	TAY - Transfer accumulator to Y register
	TSX - Transfer stack pointer to Index X
	TXS - Transfer register X to stack pointer
	TXA - Transfer register X to accumulator
	TYA - Transfer register Y to accumulator

