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

### Branch Instructions

#### BCC – Branch if Carry Flag is Clear
#### BCS – Branch if Carry Flag is Set
#### BEQ – Branch on Result Zero
#### BNE – Branch if Result is Not Zero
#### BMI – Branch on Result Minus
#### BPL – Branch on Result Plus
#### BVC – Branch on Overflow Clear
#### BVS – Branch on Overflow Set
#### BRK – Unconditional Break

---

### Stack and Subroutine Instructions

#### PHA – Push Accumulator onto the Stack
#### PHP – Push Processor Flags onto the Stack
#### PLA – Pull (Pop) Accumulator from the Stack
#### PLP – Pull (Pop) Processor Flags from the Stack
#### JSR – Jump to Subroutine
#### RTS – Return from Subroutine
#### RTI – Return from Interrupt

---

### Data Transfer Instructions

#### LDA – Load Accumulator with Constant or Memory
#### LDX – Load X Register with Constant or Memory
#### LDY – Load Y Register with Constant or Memory
#### STA – Store Accumulator in Memory
#### STX – Store X Register in Memory
#### STY – Store Y Register in Memory
#### TAX – Transfer Accumulator to X Register
#### TAY – Transfer Accumulator to Y Register
#### TSX – Transfer Stack Pointer to Index X
#### TXS – Transfer X Register to Stack Pointer
#### TXA – Transfer X Register to Accumulator
#### TYA – Transfer Y Register to Accumulator


![scan1](https://github.com/lostjared/ats/blob/master/scans/flags1.png?raw=true  "Scan 1")

![scan2](https://github.com/lostjared/ats/blob/master/scans/flags2.png?raw=true  "Scan 2")

![scan3](https://github.com/lostjared/ats/blob/master/scans/Opcodes1.png?raw=true  "Scan 3")

![scan4](https://github.com/lostjared/ats/blob/master/scans/Opcodes2.png?raw=true  "Scan 4")

