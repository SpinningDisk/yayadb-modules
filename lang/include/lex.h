#ifndef LEX_H
#define LEX_H

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

const char** _functionNames();
t_LRC lex(char* input, unsigned int input_length);


#endif