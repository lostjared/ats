#include "function.hpp"

interp::Code code;

std::unordered_map<std::string, Command> function_map = {
    { "convert",Command(token::token_Convert, 0) },
    { "list",Command(token::token_List, 0) },
    { "save",Command(token::token_Save, 2) },
    { "open",Command(token::token_Open, 2) },
    { "clear",Command(token::token_Clear, 0) },
    { "remove",Command(token::token_Remove, 1) },
    { "display",Command(token::token_Display, 1) },
    { "symbols",Command(token::token_DisplaySymbols, 0) }
};

namespace token {
    
}
