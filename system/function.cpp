#include "function.hpp"

interp::Code code;

std::unordered_map<std::string, Command> function_map = {
    { "convert",Command(token::token_Convert, 0, "Convert stored code to tokens.") },
    { "list",Command(token::token_List, 0, "List source code") },
    { "save",Command(token::token_Save, 1, "Save stored code") },
    { "open",Command(token::token_Open, 1, "Open code from file") },
    { "clear",Command(token::token_Clear, 0, "Clear all lines")},
    { "remove",Command(token::token_Remove, 1, "Remove individual line argument 1 is line number.") },
    { "display",Command(token::token_Display, 1, "Display indivdual line") },
    { "symbols",Command(token::token_DisplaySymbols, 0, "Print stored shell variable symbols") },
    { "symbol", Command(token::token_DisplaySymbol, 1, "Print indivdual symbol argument is the name") },
    { "unsym", Command(token::token_Unsym, 1, "Remove symbol from table.") },
    { "execute", Command(token::token_Execute, 0, "Execute compiled code") },
    { "help", Command(token::token_Help, 0, "Print help message") },
    { "sh", Command(token::token_sh, 1, "Execute shell command stored in argument one as a string") },
    { "html", Command(token::token_HTML, 1, "Print code info to HTML") },
    { "procinfo", Command(token::token_ProcInfo, 0, "Print registers to console") },
    { "setreg", Command(token::token_SetReg, 2, "Set register to value") },
    { "peek", Command(token::token_Peek, 1, "Show memory location argument one is memory address") },
    { "poke", Command(token::token_Poke, 2, "Store value in memory location argument one is memory argument two is value (symbol or constant)") },
    { "setsym", Command(token::token_SetSym, 2, true, "Set symbol value in Symbol Table") },
    { "tokenize", Command(token::token_Tokenize, -1, "Tokenize string") },
    { "expr", Command(token::token_Expression, -1, "Parse Expression ofor symbols") },
    { "build", Command(token::token_Build, 0, "Build code") },
    { "print", Command(token::token_Print, 0, "Print out information about built code") },
    { "code", Command(token::token_Code, 0, "Print out Hex values for Machine lanauge") },
    { "step", Command(token::token_Step, 0, "Make Step in debugger") },
    { "memory", Command(token::token_Memory, 2, "Print memory range argument one is hex value starting value range argument two is hex value stop value range") }
};

namespace token {
    
}
