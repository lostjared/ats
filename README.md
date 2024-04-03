# ATS

The main goal of this project is to facilitate self-learning in the realm of interpreters, experimenting with a range of concepts heavily influenced by "The Atari Assembler" book. While it doesn't strive for an exact reproduction and acknowledges the presence of some inaccuracies, the project is designed to enrich the learning experience.

## Prerequisites
The program requires the following tools: autoconf, automake, libtool, make, g++, and readline.

## Installation Instructions

### On macOS:
1. First, install the GNU readline library. If using OS X, compile readline6 and install it to `/usr/local/`.
2. Configure the project with a `/usr/local` prefix using the command:
    ```
    ./configure --prefix=/usr/local
    ```

### On Linux:
Simply configure and compile in the standard manner.

### Building the Project:
Execute the following commands to build the project:
```
$ ./autogen.sh
$ mkdir build
$ cd build
$ ../configure --enable-debug
$ make
```

## Project Overview
This project enhances the 6502 instruction set with additional functionalities and new instructions/features, enabling the adaptation of old code for modern computing environments. It does not aim to emulate original hardware.

In the `dbg` shell program, use the `help` command to display a list of valid commands. Utilize the PEEK/POKE commands for memory manipulation.

### Registers
- X
- Y
- Accumulator

### Processor Flags
- C = Carry bit
- Z = Zero bit
- I = Interrupt disable bit
- D = Decimal mode bit
- B = Break command bit
- 5 = Expansion bit [unused]
- Z = Overflow bit
- N = Negative bit

### Instructions
- ADC - Add Memory to Accumulator with Carry
- AND - And Memory to Accumulator
- ASL - Shift Left One Bit (memory or accumulator)
- BCC - Branch if Carry Flag is clear
- BCS - Branch if Carry Flag is set
- BEQ - Branch on result Zero
- BIT - Test bits in the accumulator with memory
- BMI - Branch on result minus
- BNE - Branch if the result is not zero
- BPL - Branch on result plus
- BRK - Unconditional break
- BVC - Branch on overflow clear
- BVS - Branch on overflow set
- CLC - Clear Carry Flag
- CLD - Clear Decimal Flag
- CLI - Clear Interrupt Flag
- CLV - Clear overflow Flag
- CMP - Compare memory and accumulator
- CPX - Compare Memory and Register X
- CPY - Compare Memory and Register Y
- DEC - Decrement Memory or accumulator
- DEX - Decrement X Register
- DEY - Decrement Y Register
- EOR - Exclusive Or memory or accumulator
- INC - Increment Memory or accumulator
- INX - Increment register X
- INY - Increment register Y
- JMP - Unconditional Jump to Code label or address
- JSR - Jump To Subroutine
- LDA - Load accumulator with constant or memory
- LDX - Load X register with constant or memory
- LDY - Load Y register with constant or memory
- LSR - Shift right one bit
- NOP - No operation
- ORA - Or accumulator with constant or memory
- PHA - Push accumulator onto the stack
- PHP - Push processor flags onto the stack
- PLA - Pull (pop) accumulator from the stack
- PLP - Pull (pop) processor flags from the stack
- ROL - Rotate bits one left
- ROR - Rotate bits one right
- RTI - Return from interrupt
- RTS - Return from subroutine
- SBC - Subtract memory and borrow from the accumulator
- SEC - Set carry flag
- SED - Set decimal flag
- SEI - Set interrupt flag
- STA - Store accumulator in memory
- STX - Store register X in memory
- STY - Store register Y in memory
- TAX - Transfer accumulator to X register
- TAY - Transfer accumulator to Y register
- TSX - Transfer stack pointer to Index X
- TXS - Transfer register X to stack pointer
- TXA - Transfer register X to accumulator
- TYA - Transfer register Y to accumulator

## Contributing
Contributions are welcome! Please feel free to submit pull requests or report issues.
Scans

![scan1](https://github.com/lostjared/ats/blob/master/scans/flags1.png?raw=true  "Scan 1")

![scan2](https://github.com/lostjared/ats/blob/master/scans/flags2.png?raw=true  "Scan 2")

![scan3](https://github.com/lostjared/ats/blob/master/scans/Opcodes1.png?raw=true  "Scan 3")

![scan4](https://github.com/lostjared/ats/blob/master/scans/Opcodes2.png?raw=true  "Scan 4")

