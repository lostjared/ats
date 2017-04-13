#include "symbol.hpp"


namespace symbol {
    
    Variable::Variable() : name(""), text(""), value(0) { }
    
    Variable::Variable(const Variable &v) {
        name = v.name;
        text = v.text;
        value = v.value;
    }
    
    Variable::Variable(const std::string &n, const std::string &t) : name(n), text(t), value(0) {
        
    }
    
    Variable::Variable(const std::string &n, const float &v) : name(n),text(""),value(v) {
        
    }
    
    Variable::Variable(const std::string &n, const std::string &t, const float &v) : name(n), text(t), value(v) {
        
    }
    
    Variable &Variable::operator=(const Variable &v) {
        name = v.name;
        text = v.text;
        value = v.value;
        return *this;
    }
    
    bool Variable::operator<(const Variable &v) const {
        if(name < v.name) return true;
        return false;
    }
}
