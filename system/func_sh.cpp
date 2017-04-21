#include "function.hpp"
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>


namespace token {
    
    int System(const std::string &command) {
        sigset_t bmask, omask;
        struct sigaction sa_ignore, sa_oquit, sa_origint, sa_default;
        pid_t id;
        int status, serrno;
        
        if(command == "") return System(":") == 0;
        
        sigemptyset(&bmask);
        sigaddset(&bmask, SIGCHLD);
        sigprocmask(SIG_BLOCK, &bmask, &omask);
        sa_ignore.sa_handler = SIG_IGN;
        sa_ignore.sa_flags = 0;
        sigemptyset(&sa_ignore.sa_mask);
        sigaction(SIGINT, &sa_ignore, &sa_origint);
        sigaction(SIGQUIT, &sa_ignore, &sa_oquit);
        
        switch((id = fork())) {
            case -1:
                status = -1;
                break;
            case 0:
                sa_default.sa_handler = SIG_DFL;
                sa_default.sa_flags = 0;
                sigemptyset(&sa_default.sa_mask);
                if(sa_origint.sa_handler != SIG_IGN)
                    sigaction(SIGINT, &sa_default, NULL);
                if(sa_oquit.sa_handler != SIG_IGN)
                    sigaction(SIGQUIT, &sa_default, NULL);
                
                execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
                _exit(127);
                break;
            default:
                while(waitpid(id, &status, 0) == -1) {
                    if(errno != EINTR) {
                        status = -1;
                        break;
                    }
                }
                break;
        }
        serrno = errno;
        sigprocmask(SIG_SETMASK, &omask, NULL);
        sigaction(SIGINT, &sa_origint, NULL);
        sigaction(SIGQUIT, &sa_oquit, NULL);
        errno = serrno;
        return status;
    }
    
    void token_sh(const std::string &command, std::vector<lex::Token> &tokens) {
        int rt_value = 0;
        if(tokens.size() >= 1) {
            if(tokens[1].getTokenType() == lex::TOKEN_STRING)
            	rt_value = System(tokens[1].getToken());
            else {
                std::cerr << "Error: sh requires one string argument in quotes\n";
                return;
            }
        }
        std::cout << "sh: returns " << rt_value << "\n";
    }
}
