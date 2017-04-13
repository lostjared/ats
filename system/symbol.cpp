#include "symbol.hpp"


namespace symbol {
    
    Symbol::Symbol() {
        
    }
    
    bool Symbol::exisits(const std::string &name) {
        auto it = var.find(name);
        if(it == var.end()) return false;
        return true;
    }
    
    void Symbol::set(const std::string &name, const Variable &v) {
        var[name] = v;
    }
    
    bool Symbol::get(const std::string &name, Variable &v) {
        auto it = var.find(name);
        if(it == var.end()) return false;
        v = it->second;
        return true;
    }
}
