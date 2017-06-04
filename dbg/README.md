https://github.com/lostjared/ats/blob/master/dbg/README.md
Command list:

quit

description: quit application

Use: quit

Command: bin

Description: Convert to Binary

Use: bin numbers

Command: build

Description: Build code

Use: build

Command: clear

Description: Clear all lines

Use: clear

Command: code

Description: Print out Hex values for Machine lanauge

Use: code

Command: continue

Description: Continue execution

Use: continue

Command: convert

Description: Convert stored code to tokens 

Use: convert

Command: debug

Description: Run program with debug information

Use: debug

Command: display

Description: Display indivdual line

Use: display line

Command: execute

Description: Execute compiled code

Use: execute

Command: expr

Description: Parse Expression for symbols

Use: expr expression

Command: help

Description: Print help message

Use: help

Command: html

Description: Print code info to HTML

Use: html "filename"

Command: insert

Description: Insert a stream of bytes at a starting address

Use: insert startaddress val1 val2 val3 ....

Command: list

Description: List source code

Use: list

Command: memory

Description: Print memory range argument one is hex value starting value range argument two is hex value stop value range

Use: memory start stop

Command: open

Description: Open code from file

Use: open "filename"

Command: peek

Description: Show memory location argument one is memory address

Use: peek address

Command: peek16

Description: Peek 16 bit value from memory.

Use: peek16 address value

Command: poke

Description: Store value in memory location argument one is memory argument two is value (symbol or constant)

Use: poke address value

Command: print

Description: Print out information about built code

Use: print

Command: procinfo

Description: Print registers to console

Use: procinfo

Command: remove

Description: Remove individual line argument 1 is line number

Use: remove index

save

Description: Save stored code

Use: save "filename"

Command: setreg

Description: Set register to value

Use: setreg register value

Command: setsym

Description: Set symbol value in Symbol Table

Use: setsym variable value

Command: sh

Description: Execute shell command stored in argument one as a string

Use: sh "command"

Command: stack

Description: Display contents of stack

Use: stack

Command: step

Description: Make Step in debugger

Use: step

Command: symbol

Description: Print indivdual symbol argument is the name

Use: symbol variable

Command: symbols

Description: Print stored shell variable symbols

Use: symbols

Command: tokenize

Description: Tokenize string

Use: tokenize string

Command: unsym

Description: Remove symbol from table

Use: unsym variable
