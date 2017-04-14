#include "symbol.hpp"


namespace symbol {
    
    Value::Value() : text(""), value(0) { }
    Value::Value(const Value &v) : text(v.text), value(v.value) { }
    Value::Value(const std::string &t, const double &v) : text(t), value(v) { }
    
    Variable::Variable() : is_array(false), array_size(0) {}
    
    Variable::Variable(const Variable &v) {
        name = v.name;
        is_array = v.is_array;
        array_size = v.array_size;
        values = v.values;
    }
    
    Variable::Variable(const std::string &n, const Value &value)  {
        name = n;
        values.reset(new Value(value));
        is_array = false;
        array_size = 0;
    }
    
    Variable::Variable(const std::string &n, const unsigned long arr_size) : is_array(true), array_size(arr_size) {
        name = n;
        values.reset(new Value[arr_size+1]);
    }
    
    Variable &Variable::operator=(const Variable &v) {
        name = v.name;
        values = v.values;
        is_array = v.is_array;
        array_size = v.array_size;
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
    
    std::ostream &operator<<(std::ostream &out, Variable &v) {
        if(v.isArray() == false)
            out << v.name << " = { \"" << v.get_text() << "\" : " << v.get_double() << " } ";
        else {
            for(unsigned int i = 0; i < v.arraySize(); ++i) {
                out << v.name << "[" << i << "] = { \"" << v.get_text(i) << "\" : " << v.get_double(i) << " }\n";
            }
        }
        return out;
    }
}
