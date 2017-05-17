/*
 
 ats - Atari Script, A Fun Practice Project
 written by Jared Bruni
 http://lostsidedead.com
 
 */

#define VERSION_INFO "1.0"
#include"code.hpp"
#include"function.hpp"
#include<unordered_map>
#include<readline/readline.h>
#include<readline/history.h>
#include<unistd.h>
#include<signal.h>


void control_Handler(int sig) {
    if(code.running()) {
        code.stop();
        std::cout << "Program break.\n";
        code.print();
    }
    else std::cout << "Caught signal: SIGINT.\n";
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main() {
    
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = control_Handler;
    
    if(sigaction(SIGINT, &sa, 0) == -1) {
        std::cerr << "Error on sigaction:\n";
        exit(EXIT_FAILURE);
    }
    
    
    code.symbols["version"].create("version", symbol::Value(VERSION_INFO, 1.0));
    code.symbols["author"].create("author", symbol::Value("lostjared", 0));
    std::ios state(0);
    state.copyfmt(std::cout);
    
    std::cout << "ats (atari script) interactive debugger v" << VERSION_INFO << "\nPress Ctrl+C to break program.\nUse help command for more information on commands.\n";
    
    while(1) {
        try {
            
            std::string input_line;
            char *input = readline("$>");
            add_history(input);
            input_line = input;
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
            first_token = icode::lcase(v[0].getToken());
            if(first_token == "quit") break;
            auto rt = function_map.find(first_token);
            if(rt == function_map.end()) {
                interp::inputText(v, input_line);
                continue;
            }
            
            int token_count = v.size()-1;
            if((rt->second.greater == false && token_count == rt->second.args) || (rt->second.args == -1) || (rt->second.greater == true && token_count >= rt->second.args)) rt->second.func(input_line, v);
            else {
                std::cout.copyfmt(state);
                std::cout << "Error: " << first_token << " requires: " << rt->second.args << " arguments. You gave " << token_count << "\n";
                continue;
            }
            std::cout.copyfmt(state);
        }
        catch(lex::Scanner_EOF) {
            
        }
        catch(lex::Scanner_Error &e) {
            std::cerr << "Error: " << e.error_text << "\n";
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
