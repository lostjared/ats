#include "function.hpp"

interp::Code code;

std::unordered_map<std::string, Command> function_map = {
    { "convert",Command(token::token_Convert, 0) },
    { "list",Command(token::token_List, 0) },
    { "save",Command(token::token_Save, 1) },
    { "open",Command(token::token_Open, 1) },
    { "clear",Command(token::token_Clear, 0) },
    { "remove",Command(token::token_Remove, 1) },
    { "display",Command(token::token_Display, 1) },
    { "symbols",Command(token::token_DisplaySymbols, 0) },
    { "symbol", Command(token::token_DisplaySymbol, 1) },
    { "unsym", Command(token::token_Unsym, 1) },
    { "execute", Command(token::token_Execute, 0) },
    { "help", Command(token::token_Help, 0) },
    { "sh", Command(token::token_sh, 1) },
    { "html", Command(token::token_HTML, 1) },
    { "procinfo", Command(token::token_ProcInfo, 0) },
    { "setreg", Command(token::token_SetReg, 2) },
    { "peek", Command(token::token_Peek, 1) },
    { "poke", Command(token::token_Poke, 2) },
    { "setsym", Command(token::token_SetSym, 2, true) },
    { "tokenize", Command(token::token_Tokenize, -1) },
    { "expr", Command(token::token_Expression, -1) },
    { "build", Command(token::token_Build, 0) },
    { "print", Command(token::token_Print, 0) },
    { "code", Command(token::token_Code, 0) },
    { "step", Command(token::token_Step, 0) }
};

namespace token {
    
}
