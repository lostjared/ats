# ATS

![6502](https://github.com/user-attachments/assets/32f0bd69-8a24-431d-8a4e-dc2921dc244a)


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

## Registers and Processor Flags

### Registers

- **Accumulator (A):**  
  The primary register used for arithmetic, logic, and data transfer operations.

- **X Register:**  
  Often used for indexing memory addresses, loop counters, and other auxiliary operations.

- **Y Register:**  
  Also used for indexing and addressing, particularly in conjunction with the accumulator.

### Processor Flags

The status register is made up of several bits that indicate the outcome of operations. The flags are:

- **C – Carry Flag:**  
  Set if an arithmetic operation produces a carry out of the most significant bit (addition) or if a borrow is needed (subtraction).

- **Z – Zero Flag:**  
  Set if the result of an operation is zero.

- **I – Interrupt Disable Flag:**  
  When set, maskable interrupts are disabled.

- **D – Decimal Mode Flag:**  
  When set, arithmetic operations are performed in binary-coded decimal (BCD) mode.

- **B – Break Command Flag:**  
  Set when a BRK instruction has been executed.

- **5 – Unused/Expansion Bit:**  
  Typically unused or reserved for future use.

- **V – Overflow Flag:**  
  Set if an arithmetic overflow occurs (i.e., the result is too large for the register).

- **N – Negative Flag:**  
  Set if the result of an operation is negative (i.e., the most significant bit is 1).

---

## Instruction Set Overview

Below is a categorized list of the 6502 instructions with detailed explanations.

### Arithmetic and Logical Instructions

#### ADC – Add Memory to Accumulator with Carry
- **Mnemonic:** `ADC`
- **Purpose:** Adds the contents of a memory location (or immediate value) to the accumulator along with the carry flag.
- **Usage:**  
  ```asm
  ADC operand
  ```
- **Example:**  
  ```asm
  LDA #$05   ; Load 5 into the accumulator
  CLC        ; Clear the carry flag
  ADC #$03   ; Add 3 to A; A now equals 8
  ```

#### AND – And Memory to Accumulator
- **Mnemonic:** `AND`
- **Purpose:** Performs a bitwise AND between the accumulator and a memory operand.
- **Usage:**  
  ```asm
  AND operand
  ```

#### EOR – Exclusive Or memory or accumulator
- **Mnemonic:** `EOR`
- **Purpose:** Performs a bitwise exclusive OR (XOR) between the accumulator and an operand.

#### ORA – Or accumulator with constant or memory
- **Mnemonic:** `ORA`
- **Purpose:** Performs a bitwise OR between the accumulator and an operand.

#### SBC – Subtract Memory and Borrow from the Accumulator
- **Mnemonic:** `SBC`
- **Purpose:** Subtracts a memory operand and the inverse of the carry flag from the accumulator.

---

### Shift, Rotate, and Bit-Test Instructions

#### ASL – Shift Left One Bit (memory or accumulator)
- **Mnemonic:** `ASL`
- **Purpose:** Shifts all bits in the specified operand one bit to the left.

#### LSR – Shift Right One Bit
- **Mnemonic:** `LSR`
- **Purpose:** Shifts all bits in the operand one bit to the right.

#### ROL – Rotate Bits One Left
- **Mnemonic:** `ROL`
- **Purpose:** Rotates the bits in the operand to the left through the carry flag.

#### ROR – Rotate Bits One Right
- **Mnemonic:** `ROR`
- **Purpose:** Rotates the bits in the operand to the right through the carry flag.

#### BIT – Test Bits in the Accumulator with Memory
- **Mnemonic:** `BIT`
- **Purpose:** Tests bits in a memory operand by performing a bitwise AND with the accumulator.

---
### All Instructions
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



![scan1](https://github.com/lostjared/ats/blob/master/scans/flags1.png?raw=true  "Scan 1")

![scan2](https://github.com/lostjared/ats/blob/master/scans/flags2.png?raw=true  "Scan 2")

![scan3](https://github.com/lostjared/ats/blob/master/scans/Opcodes1.png?raw=true  "Scan 3")

![scan4](https://github.com/lostjared/ats/blob/master/scans/Opcodes2.png?raw=true  "Scan 4")

