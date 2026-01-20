#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#include "../include/lex.h"
#include "../include/vm.h"
#include "../include/socket.h"


void runSimpleServerOnFunction(t_LRC (*f)(char*, unsigned int)){
    t_Server s = prepareServer("/tmp/mysock.sock");
    while(1){
        t_Response resp = getNextMessage(s.server_fd);
        if(resp.message_length>0){
            t_LRC ret = f(resp.message, resp.message_length);
            if(ret.facs[1]==1){
                printf("Hello from main!\n\tgot code \"exit\":3\nBye!\n");
                return;
            }
        }
    }
    return;
}
int main(){
    runSimpleServerOnFunction(&lex);
    return 0;
}