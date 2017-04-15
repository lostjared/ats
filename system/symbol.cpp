#include "symbol.hpp"


namespace symbol {
    
    Symbol::Symbol() {
        
    }
    
    Symbol::Symbol(const Symbol &s) : var(s.var) {
        
    }
    Symbol::Symbol(const Symbol &&s) : var(std::move(s.var)) {
        
    }
    Symbol &Symbol::operator=(const Symbol &s) {
        var = s.var;
        return *this;
    }
    
    Symbol &Symbol::operator=(const Symbol &&s) {
        var = std::move(s.var);
        return *this;
    }
    
    
    bool Symbol::exisits(const std::string &name) {
        auto it = var.find(name);
        if(it == var.end()) return false;
        return true;
    }
    
    void Symbol::set(const Variable &v) {
        var[v.name] = v;
    }
    
    bool Symbol::get(const std::string &name, Variable &v) {
        auto it = var.find(name);
        if(it == var.end()) return false;
        v = it->second;
        return true;
    }
    
    Variable &Symbol::operator[](const std::string &index) {
        return var[index];
    }
    
    void Symbol::list_sorted(std::ostream &out) {
        std::vector<Variable> var_;
        for(auto i = var.begin(); i != var.end(); ++i) {
            var_.push_back(i->second);
        }
        std::sort(var_.begin(), var_.end());
        for(auto z = var_.begin(); z != var_.end(); ++z) {
            std::cout << *z << "\n";
        }
    }
    
    void Symbol::clear() {
        if(!var.empty()) {
            var.erase(var.begin(), var.end());
        }
    }
    
    std::ostream &operator<<(std::ostream &out, Symbol &s) {
        s.list_sorted(out);
        return out;
    }
}
