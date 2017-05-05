#include "function.hpp"


namespace token {
    
    class SortedCommand {
    public:
        SortedCommand() {}
        std::string name;
        Command cmd;
        SortedCommand(const SortedCommand &c) : name(c.name), cmd(c.cmd) {}
        
        SortedCommand &operator=(const SortedCommand &c) {
            name = c.name;
            cmd = c.cmd;
            return *this;
        }
        
        SortedCommand(std::string n, Command c) {
            name = n;
            cmd = c;
        }
        
        bool operator<(const SortedCommand &e) const {
            return (name < e.name);
        }
    };
    
    void token_Help(const std::string &command, std::vector<lex::Token> &tokens) {
        std::cout << "Command list:\n\nquit\ndescription: quit application\n\n";
        static std::vector<SortedCommand> names;
        if(names.size() == 0) {
            for(auto i = function_map.begin(); i != function_map.end(); ++i) {
                names.push_back(SortedCommand(i->first, i->second));
            }
            std::sort(names.begin(), names.end());
        }
        for(auto i = names.begin(); i != names.end(); ++i) {
            std::cout << i->name  << "\n" "description: " <<  i->cmd.help_text << "\n\n";
        }
    }
}
