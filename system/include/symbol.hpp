#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include<iostream>
#include<string>
#include<unordered_map>

namespace symbol {
    
    class Variable {
    public:
        std::string name;
        std::string text;
        float value;
        
        Variable();
        Variable(const Variable &v);
        Variable &operator=(const Variable &v);
    };
    
    class Symbol {
    public:
        Symbol();
        bool exisits(const std::string &name);
        void set(const std::string &name, const Variable &v);
        bool get(const std::string &name, Variable &v);
        Variable &operator[](std::string index);
        
    protected:
        std::unordered_map<std::string, Variable> var;
    };
}

#endif
