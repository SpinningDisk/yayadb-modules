#include <Python.h>
#include "../include/socket.h"
#include <string.h>
#include <malloc.h>

#define PROTO_INIT_MOD_COUNT        4
#define PROTO_MOD_CACHE_SIZE        8
#define PROTO_INIT_OBJ_COUNT         16
#define PROTO_OBJ_INCR                         4
#define PROTO_MOD_INCR                         4

int getStrIndex(char* elm, char** arr, unsigned int arr_length){
    for(unsigned int i=0; i<arr_length;i++){
        int passesCheck = 1;
        for(unsigned int j=0; j<strlen(arr[i]); j++){
            if(strcmp(elm, arr[i])!=0){
                passesCheck = 0;
                break;
            }
        }
        if(passesCheck){
            return i;
        }
    }
    return -1;
}

typedef struct s_ProtoState{
    PyObject** objects;
    unsigned int object_count;
    unsigned int object_count_allocated;
    
    PyObject** modules;
    unsigned int modules_count;
    unsigned int modules_count_allocated;
    
    PyObject*** module_cache;
    unsigned int* module_cache_index;
    
    t_Server server;
}t_ProtoState;

t_ProtoState* _initProto_(const char* server_name){
    // fill fields
    t_ProtoState *proto = (t_ProtoState*)malloc(sizeof(t_ProtoState));
    
    proto->objects = (PyObject**)malloc(PROTO_INIT_OBJ_COUNT*sizeof(PyObject*));
    proto->object_count_allocated = PROTO_INIT_OBJ_COUNT;
    proto->object_count = 0;
    
    proto->modules = (PyObject**)malloc(PROTO_INIT_MOD_COUNT*sizeof(PyObject*));
    proto->object_count_allocated = PROTO_INIT_MOD_COUNT;
    proto->object_count = 0;
    
    proto->module_cache = (PyObject***)malloc(PROTO_INIT_MOD_COUNT*sizeof(PyObject**));
    for(int i=0; i<PROTO_INIT_MOD_COUNT; i++){
        proto->module_cache[i] = (PyObject**)malloc(sizeof(PyObject*)*PROTO_MOD_CACHE_SIZE);
    }
    proto->module_cache_index = calloc(PROTO_MOD_CACHE_SIZE, sizeof(unsigned int));
    proto->server = prepareServer(server_name);
    printf("got here\n:3\n");


    // get necessary modules
    // 0: pickle;   1: ???  2: ???  3: ???
    proto->modules[0] = PyImport_ImportModule("pickle");

    // get common functions of modules and fill cache
    proto->module_cache[0][1] = PyObject_GetAttrString(proto->modules[0], "dumps");
    return proto;
}
t_ProtoState* checkProtoAllocations(t_ProtoState* proto){
    if(proto->object_count>=proto->object_count_allocated){
        proto->object_count_allocated += PROTO_OBJ_INCR;
        proto->objects = realloc(proto->objects, (proto->object_count_allocated)*sizeof(PyObject*));
    }
    if(proto->modules_count>=proto->modules_count_allocated){
        proto->modules_count_allocated += PROTO_MOD_INCR;
        proto->modules  = realloc(proto->modules, (proto->modules_count_allocated)*sizeof(PyObject*));
    }
    return proto;
}
t_ProtoState* answer(t_ProtoState *proto){
    PyObject *obj = PyLong_FromLong(42);
    proto = checkProtoAllocations(proto);
    proto->objects[proto->object_count] = obj;
    proto->object_count++;
    return proto;
}