#ifndef SOCKET_H
#define SOCKET_H

struct sockaddr_un{};
typedef struct s_Response{
    char* message;
    unsigned int message_length;
    int client_fd;
}t_Response; 
typedef struct s_Server{
    int server_fd;
    int client_fd;
    struct sockaddr_un addr;
}t_Server;

t_Response getNextMessage(int server_fd);
t_Server prepareServer(const char* name);

#endif