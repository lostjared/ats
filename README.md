# ats

Work in progress. In early stages still, but the goal of this project is to teach myself more about interpreters.

to build:

$ ./autogen.sh

$ mkdir build

$ cd build

$ ../configure --enable-debug

$ make 


This project is based on 6502 Instructions 
with added functionality and new instructions / features to
allow this program to be used on modern computers.

Base instruction set:

PEEK / POKE


	The Processor Flags

	0 = Negative Result Flag

	1 = Overflow Flag

	2 = Expansion Flag (Not Labeled)

	3 = Break Command Flag

	4 = Decimal Mode Flag

	5 = Intereupt disable flag

	6 = Zero result flag

	7 = Carry Flag
	

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

TXA - Transfer register X to accumulator

TYA - Transfer register Y to accumulator


