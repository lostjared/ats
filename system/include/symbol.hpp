#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<memory>

namespace symbol {
    
    class Value {
    public:
        std::string text;
        double value;
        Value();
        Value(const Value &v);
        Value(const std::string &text, const double &value);
    };
    
    class Variable {
    public:
        std::string name;
        std::shared_ptr<Value> values;
        Variable();
        Variable(const Variable &v);
        Variable(const std::string &name, const Value &v);
        Variable(const std::string &name, const unsigned long arr_size);
        Variable &operator=(const Variable &v);
        bool operator<(const Variable &v) const;
        
        std::string &get_text();
        std::string &get_text(unsigned long index);
        double &get_double();
        double &get_double(unsigned long index);
        
        bool isArray() const { return is_array; }
        unsigned long arraySize() const { return array_size; }
        
        friend std::ostream &operator<<(std::ostream &out, Variable &v);
    private:
        bool is_array;
        unsigned long array_size;
    };
    
    
    class Symbol {
    public:
        Symbol();
        Symbol(const Symbol &s);
        Symbol(const Symbol &&s);
        Symbol &operator=(const Symbol &s);
        Symbol &operator=(const Symbol &&s);
        bool empty() const { return var.empty(); }
        bool exisits(const std::string &name);
        void set(const Variable &v);
        bool get(const std::string &name, Variable &v);
        Variable &operator[](const std::string &index);
        void list_sorted(std::ostream &out);
        void clear();
        friend std::ostream &operator<<(std::ostream &out, Symbol &s);
    protected:
        std::unordered_map<std::string, Variable> var;
    };
    
    
}

#endif
