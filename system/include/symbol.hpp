#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm>

namespace symbol {
    
    class Variable {
    public:
        std::string name;
        std::string text;
        float value;
        
        Variable();
        Variable(const Variable &v);
        Variable(const std::string &name, const std::string &text);
        Variable(const std::string &name, const float &v);
        Variable(const std::string &name, const std::string &text, const float &v);
        Variable &operator=(const Variable &v);
        bool operator<(const Variable &v) const;
    };
    
    class Symbol {
    public:
        Symbol();
        Symbol(const Symbol &s);
        Symbol(const Symbol &&s);
        Symbol &operator=(const Symbol &s);
        Symbol &operator=(const Symbol &&s);
        
        bool exisits(const std::string &name);
        void set(const std::string &name, const Variable &v);
        bool get(const std::string &name, Variable &v);
        Variable &operator[](const std::string &index);
        
        void list_sorted(std::ostream &out);
        void clear();
        
    protected:
        std::unordered_map<std::string, Variable> var;
    };
}

#endif
