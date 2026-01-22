#include "../include/socket.h"
#include "../include/proto.h"
#include <Python.h>
#include <stdio.h>

#define code_length 3
#define server_name "sockets/proto_test.sock"
int hanspeter(int* test){
    printf("\taddress to hanspeter: %p\n", test);
    return *test;
}
int main(){
    Py_Initialize();
    // printf("hello from test!\n\tname is %s\n", server_name);
    // t_ProtoState proto = *_initProto_(server_name);
    /*char* codes[code_length] = {"exit", "print", "answer"};
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
            // proto= *answer(&proto);
            // printf("[testing] the answer to live, death and the universe is: %d (at address %p)\n", PyLong_AsLong(proto.objects[proto.object_count]), proto.objects[proto.object_count]);
            printf("[testing]\n");
        }
    }
    return 0;*/
    
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("print(sys.path)");
    PyObject* pickle = PyImport_ImportModule("pickle");
    if(pickle==NULL){
        PyErr_Print();
        fprintf(stderr, "Error while importing Module \"pickle\"\n");
        return -1;
    }
    printf(">:3\n");
    PyObject* dumps = PyObject_GetAttrString(pickle, "dumps");
    if(dumps==NULL){
        fprintf(stderr, "Error while getting method \"dumps\" of module \"pickle\"\n");
        return -2;
    }
    printf(":3\n");
    printf("dumps at %p (with pickle at %p with starting word %d) with starting word %d\n", dumps, pickle, *(int*)(void*)pickle, *(int*)(void*)dumps);
    t_ProtoState proto = *_initProto_(server_name);
    // printf("[TESTING]  testServer:\n\t\tserver_fd: %d (at %p)\n\t\taddr at %p\n", proto.server.server_fd, &proto.server.server_fd, &proto.server.addr);
    return 0;
}