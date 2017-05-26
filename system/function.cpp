#include "function.hpp"

interp::Code code;

std::unordered_map<std::string, Command> function_map = {
    { "convert",Command(token::token_Convert, 0, "Convert stored code to tokens \nUse:\nconvert") },
    { "list",Command(token::token_List, 0, "List source code\nUse:\nlist") },
    { "save",Command(token::token_Save, 1, "Save stored code\nUse:\nsave \"filename\"") },
    { "open",Command(token::token_Open, 1, "Open code from file\nUse:\nopen \"filename\"") },
    { "clear",Command(token::token_Clear, 0, "Clear all lines\nUse:\nclear")},
    { "remove",Command(token::token_Remove, 1, "Remove individual line argument 1 is line number\nUse:\nremove index") },
    { "display",Command(token::token_Display, 1, "Display indivdual line\nUse:\ndisplay line") },
    { "symbols",Command(token::token_DisplaySymbols, 0, "Print stored shell variable symbols\nUse:\nsymbols") },
    { "symbol", Command(token::token_DisplaySymbol, 1, "Print indivdual symbol argument is the name\nUse:\nsymbol variable") },
    { "unsym", Command(token::token_Unsym, -1, "Remove symbol from table\nUse:\nunsym variable") },
    { "execute", Command(token::token_Execute, 0, "Execute compiled code\nUse:\nexecute") },
    { "help", Command(token::token_Help, -1, "Print help message\nUse:\nhelp") },
    { "sh", Command(token::token_sh, 1, "Execute shell command stored in argument one as a string\nUse:\nsh \"command\"") },
    { "html", Command(token::token_HTML, 1, "Print code info to HTML\nUse:\nhtml \"filename\"") },
    { "procinfo", Command(token::token_ProcInfo, 0, "Print registers to console\nUse:\nprocinfo") },
    { "setreg", Command(token::token_SetReg, 2, "Set register to value\nUse:\nsetreg register value") },
    { "peek", Command(token::token_Peek, 1, "Show memory location argument one is memory address\nUse:\npeek address") },
    { "poke", Command(token::token_Poke, 2, "Store value in memory location argument one is memory argument two is value (symbol or constant)\nUse:\npoke address value") },
    { "setsym", Command(token::token_SetSym, 2, true, "Set symbol value in Symbol Table\nUse:\nsetsym variable value") },
    { "tokenize", Command(token::token_Tokenize, -1, "Tokenize string\nUse:\ntokenize string") },
    { "expr", Command(token::token_Expression, -1, "Parse Expression ofor symbols\nUse:\nexpr expression") },
    { "build", Command(token::token_Build, 0, "Build code\nUse:\nbuild") },
    { "print", Command(token::token_Print, 0, "Print out information about built code\nUse:\nprint") },
    { "code", Command(token::token_Code, 0, "Print out Hex values for Machine lanauge\nUse:\ncode") },
    { "step", Command(token::token_Step, 0, "Make Step in debugger\nUse:\nstep") },
    { "memory", Command(token::token_Memory, 2, "Print memory range argument one is hex value starting value range argument two is hex value stop value range\nUse:\nmemory start stop") },
    { "peek16", Command(token::token_Peek16, 1, "Peek 16 bit value from memory.\nUse:peek16 address value") },
    { "insert", Command(token::token_Insert, -1, "Insert a stream of bytes at a starting address\nUse: insert startaddress val1 val2 val3 ....") },
    { "continue", Command(token::token_Continue, 0, "Continue execution\nUse: continue") },
    { "debug", Command(token::token_Debug, 0, "Run program with debug information\nUse: debug") },
    { "stack", Command(token::token_Stack, 0, "Display contents of stack\nUse: stack") }
};

namespace token {
    
}
