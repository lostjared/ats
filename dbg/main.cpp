/*
 
 ats - Practice Project
 written by Jared Bruni
 http://lostsidedead.com
 
 */

#include"code.hpp"
#include"function.hpp"
#include<unordered_map>

int main() {
    code.symbols["pi"].create("pi", symbol::Value("INF", 0));
    
    double &pi = code.symbols["pi"].get_double();
    pi = 3.14159265359;
        
    while(1) {
        try {
            std::cout << "$> ";
            std::string input_line;
            std::getline(std::cin, input_line);
            std::istringstream stream(input_line);
            lex::Scanner scan(stream);
            std::vector<lex::Token> v;
            while(scan.valid()) {
                lex::Token s;
                scan >> s;
                if(s.getTokenType() != lex::TOKEN_EOF)
                	v.push_back(s);
            }
            if(v.size()==0) continue;
            std::string first_token;
            first_token = v[0].getToken();
            if(first_token == "quit") break;
            auto rt = function_map.find(first_token);
            if(rt == function_map.end()) {
                interp::inputText(v, input_line);
                continue;
            }
            
            int token_count = v.size()-1;
            if(token_count == rt->second.args) rt->second.func(input_line, v);
            else {
                std::cout << "Error " << first_token << " requires: " << rt->second.args << " arguments. You gave " << token_count << "\n";
            }
        }
        catch(lex::Scanner_EOF) {
            
        }
        catch(lex::Scanner_Error) {
            std::cerr << "Scanner Error has occured.\n";
        }
        catch(std::exception &e) {
            std::cerr << "System Exception thrown: " << e.what() << "\n";
        }
        catch(...) {
            std::cerr << "Unknown Exception thrown...\n";
        }
    }
    return EXIT_SUCCESS;
}
