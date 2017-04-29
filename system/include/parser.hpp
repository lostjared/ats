#ifndef __PARSER__H__
#define __PARSER__H__

#include "lexer.hpp"

namespace lex {
    
    typedef double (*call_function)(double d);
    struct Func {
        std::string name;
        call_function func;
    };

    double app_exit(double d);
    double app_clear(double d);
    
    extern std::unordered_map<std::string, Func> function;
    
    class Parser : public Scanner {
        
    public:
        explicit Parser(std::istream *stream) : Scanner{stream} {}
        explicit Parser(std::istream &stream) : Scanner{stream} {}
        bool eval();
        double prim(bool get);
        double term(bool get);
        double expr(bool get);
    };
}

#endif
