# ats

The primary objective is self-education on interpreters. It experiments with various concepts, drawing significant inspiration from the book "the Atari Assembler". While not a precise replication, and despite some errors, it's aimed at providing a valuable learning experience.

Necessary tools for the program include: autoconf, automake, libtool, make, g++, and readline."

First you need to install the GNU readline library
if on OS X compile readline6 then install to /usr/local/

and configure project with /usr/local prefix

./configure --prefix=/usr/local

on Linux just configure and compile as normal.

to build:

$ ./autogen.sh

$ mkdir build

$ cd build

$ ../configure --enable-debug

$ make 


This project is based on 6502 Instructions 
with added functionality and new instructions / features to
allow this old code to be used on modern computers. Emulation of original hardware is not the goal of this project.

in the shell program dbg use help command to print list of accepted commands
and use PEEK/POKE commands to manipulate memory

Registers: 

	X
	Y
	Accumulator

Base instruction set

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
	AND - And Memory to Accumulator
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

Scans

![scan1](https://github.com/lostjared/ats/blob/master/scans/flags1.png?raw=true  "Scan 1")

![scan2](https://github.com/lostjared/ats/blob/master/scans/flags2.png?raw=true  "Scan 2")

![scan3](https://github.com/lostjared/ats/blob/master/scans/Opcodes1.png?raw=true  "Scan 3")

![scan4](https://github.com/lostjared/ats/blob/master/scans/Opcodes2.png?raw=true  "Scan 4")

