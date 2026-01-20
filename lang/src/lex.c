#include <pcre.h>
#include <string.h>
#include <stdio.h>


struct s_LexerNode;
typedef struct s_LexerNode{
    char* contents;
    unsigned int contents_length;
    struct s_LexerNode* children;
}t_LN;
typedef struct s_LexerReturnCode{
    t_LN* contents;
    unsigned int nodes;
    void* info;
    int* facs;
}t_LRC;

const char** _functionNames(){
    static const char* names[] = {"exit", "print"};
    return names;
}

// 
inline int get_string_index(char* elm, unsigned int elm_length, char** arr, unsigned int* arr_elm_lenth, unsigned int arr_length){
    for(int i=0; i<arr_length){
        int passesCheck = 1;
        for(int j=0; j<strlen(arr[j]); j++){
            if(elm!=arr[i][j]){
                passesCheck = 0;
                break;
            }
        }
        if(passesExitCheck){
            return i;
        }
    }
    return -1;

}
t_LRC lex(char* input, unsigned int input_length){
    t_LRC resp;
    resp.nodes = 0;
    resp.info = (void*)malloc(sizeof(int)*1);
    resp.facs = (int*)malloc(sizeof(int)*8);
    
    const char* trash1;
    int trash2;
    pcre* code = pcre_compile("(\\w+)\\(([a-zA-Z_]\\w*)\\)", 0, &trash1, &trash2, NULL);
    pcre_extra* study = pcre_study(code, 0, &trash1);
    int* output = malloc(sizeof(int)*64);

    int offset = 0;
    int ret = pcre_exec(code, study, input, input_length, offset, 0, output, 64);
    while(ret>0){
        printf("got match %d:\n", ret);
        short stop = 0;
        for(int i=0; i<ret; i++){
            int start = output[2*i];
            int end = output[2*i+1];
            if(start>=0&&end>=0&&end>=start){
                if(i==1){
                    // check for functions
                    // (if in group 1, we are in fucntion name)
                    int index = get_string_index(*(char*)(input+start+j), )
                }
                printf("\t%d: %.*s\n", i, end-start, input+start);
                offset = end;
                int ret = pcre_exec(code, study, input, input_length, offset, 0, output, 64);
            }else{
                stop=1;
                break;
            }
        }
        if(stop){
            break;
        }
    }
    return resp;
}