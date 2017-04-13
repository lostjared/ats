#include "symbol.hpp"


namespace symbol {
    
    Variable::Variable() : name(""), text(""), value(0) { }
    
    Variable::Variable(const Variable &v) {
        name = v.name;
        text = v.text;
        value = v.value;
    }
    
    Variable &Variable::operator=(const Variable &v) {
        name = v.name;
        text = v.text;
        value = v.value;
        return *this;
    }
}
