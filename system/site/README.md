# ATS (Assembly Script) - Web Interface

A modern web-based 6502 assembly language debugger built with WebAssembly and C++.

## 🚀 Features

### Core Functionality
- **Real-time Assembly Compilation**: Write and compile 6502 assembly code directly in the browser
- **Interactive Debugger**: Step through instructions with visual feedback
- **Memory Viewer**: Inspect and modify memory contents with hexadecimal grid display
- **Processor State Monitoring**: Real-time view of registers, flags, and stack pointer
- **HTML Report Generation**: Detailed analysis reports with instruction breakdown

### Web Interface
- **Syntax-highlighted Code Editor**: Built-in editor with assembly syntax support
- **Responsive Design**: Works on desktop and mobile devices
- **Dark Theme**: Professional dark interface optimized for long coding sessions
- **Real-time Status Updates**: Live feedback on compilation and execution status

## 🛠️ Technology Stack

- **Backend**: C++ with Emscripten WebAssembly compilation
- **Frontend**: Vanilla HTML5, CSS3, and JavaScript
- **Build System**: GNU Autotools (autoconf, automake, libtool)
- **Emulator**: Custom 6502 processor implementation
- **Assembly Parser**: Custom lexer and parser for 6502 assembly syntax

## 📁 Project Structure

```
ats/
├── system/              # Core C++ emulator code
│   ├── include/         # Header files
│   ├── site/           # Web interface files
│   │   └── index.html  # Main web interface
│   ├── *.cpp           # Source files
│   └── Makefile.am     # Build configuration
├── build/              # Build output directory
├── dbg/                # Debug build configuration
├── atari/              # Atari-specific files
├── autogen.sh          # Build system generator
├── configure.ac        # Autotools configuration
└── README.md          # This file
```

## 💻 Usage

### Writing Assembly Code

The web interface supports standard 6502 assembly syntax:

```assembly
10 CLC          ; Clear carry flag
20 LDA #100     ; Load accumulator with immediate value 100
30 ADC #50      ; Add 50 to accumulator
40 STA $10      ; Store result at memory location $10
50 END          ; End program
```

### Supported Instructions

The emulator supports the complete 6502 instruction set including:

- **Load/Store**: LDA, LDX, LDY, STA, STX, STY
- **Arithmetic**: ADC, SBC, INC, DEC, INX, INY, DEX, DEY
- **Logic**: AND, ORA, EOR
- **Shifts**: ASL, LSR, ROL, ROR
- **Branches**: BCC, BCS, BEQ, BNE, BMI, BPL, BVC, BVS
- **Jumps**: JMP, JSR, RTS, RTI
- **Stack**: PHA, PLA, PHP, PLP
- **Flags**: CLC, SEC, CLD, SED, CLI, SEI, CLV
- **Compare**: CMP, CPX, CPY
- **Transfer**: TAX, TAY, TXA, TYA, TSX, TXS
- **System**: BRK, NOP, END

### Addressing Modes

- **Immediate**: `LDA #$FF`
- **Zero Page**: `LDA $10`
- **Zero Page,X**: `LDA $10,X`
- **Zero Page,Y**: `LDX $10,Y`
- **Absolute**: `LDA $1000`
- **Absolute,X**: `LDA $1000,X`
- **Absolute,Y**: `LDA $1000,Y`
- **Indirect**: `JMP ($1000)`
- **Indexed Indirect**: `LDA ($10,X)`
- **Indirect Indexed**: `LDA ($10),Y`

### Web Interface Controls

1. **Load Example**: Choose from predefined assembly examples
2. **Build Code**: Compile your assembly code
3. **Step**: Execute instructions one at a time
4. **Reset**: Reset processor state
5. **Memory**: View/edit memory contents
6. **Generate Report**: Create detailed HTML analysis

## 🐛 Debugging Features

### Processor State Display
- **Registers**: A, X, Y, Stack Pointer
- **Flags**: Carry, Zero, Interrupt, Decimal, Break, Overflow, Negative
- **Program Counter**: Current instruction address

### Memory Inspector
- **Hexadecimal Grid**: 16x16 memory display
- **Address Navigation**: Jump to specific memory locations
- **Live Updates**: Memory changes highlighted during execution
- **Editable Values**: Click to modify memory contents

### Instruction Analysis
- **Disassembly View**: Machine code to assembly mapping
- **Execution Trace**: Step-by-step execution history
- **Timing Information**: Cycle counts and performance metrics

## 🔧 Development

### Adding New Instructions

1. Add opcode to `system/include/icode.hpp`
2. Implement instruction in `system/instructions.cpp`
3. Add opcode mapping in `system/code.cpp`
4. Update addressing mode support

### Extending the Web Interface

The web interface uses vanilla JavaScript with a modular structure:

- **Core Logic**: Assembly compilation and execution
- **UI Components**: Responsive interface elements
- **Debug Tools**: Memory viewer and processor state display
- **Mock Mode**: Fallback when WebAssembly is unavailable

## 📄 License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.

