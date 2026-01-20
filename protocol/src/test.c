#include "../include/socket.h"
#include "../include/proto.h"
#include <Python.h>
#include <stdio.h>

#define code_length 3
#define server_name "sockets/proto_test.sock"

int main(){
    Py_Initialize();
    t_ProtoState proto = *_initProto_(server_name);
    char* codes[code_length] = {"exit", "print", "answer"};
    t_Server s = prepareServer(server_name);
    while(1){
        t_Response resp= getNextMessage(s.server_fd);
        int code = getStrIndex(resp.message, codes, code_length);
        if(code==0){
            printf("got exit!\n\t:3c bye!\n");
            return 0;
        }
        if(code==1){
            printf("printing stuff...\n");
        }
        if(code==2){
            proto= *answer(&proto);
            printf("[testing] the answer to live, death and the universe is: %d (at address %p)\n", PyLong_AsLong(proto.objects[proto.object_count]), proto.objects[proto.object_count]);
        }
    }
    return 0;
}