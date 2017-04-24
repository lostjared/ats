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
    { "procinfo", Command(token::token_ProcInfo, 0) }
};

namespace token {
    
}
