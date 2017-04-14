#include "symbol.hpp"


namespace symbol {
    
    Value::Value() : text(""), value(0) { }
    Value::Value(const Value &v) : text(v.text), value(v.value) { }
    Value::Value(const std::string &t, const double &v) : text(t), value(v) { }
    
    Variable::Variable() : is_array(false) {}
    
    Variable::Variable(const Variable &v) {
        name = v.name;
        is_array = v.is_array;
        values = v.values;
    }
    
    Variable::Variable(const std::string &n, const Value &value)  {
        name = n;
        values.reset(new Value(value));
    }
    
    Variable::Variable(const std::string &n, const unsigned long arr_size) : is_array(true), array_size(arr_size) {
        name = n;
        values.reset(new Value[arr_size+1]);
    }
    
    Variable &Variable::operator=(const Variable &v) {
        name = v.name;
        values = v.values;
        return *this;
    }
    
    bool Variable::operator<(const Variable &v) const {
        if(name < v.name) return true;
        return false;
    }
    
    std::string &Variable::get_text(unsigned long index) {
        return values.get()[index].text;
    }
    
    std::string &Variable::get_text() {
        return (*values.get()).text;
    }
    
    double &Variable::get_double() {
        return (*values.get()).value;
    }
    
    double &Variable::get_double(unsigned long index) {
        return values.get()[index].value;
    }
}
