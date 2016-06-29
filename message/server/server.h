#ifndef __H_MESSAGE_LISTENER__
#define __H_MESSAGE_LISTENER__

#define BUFFER_SIZE 1500

typedef struct {
    int port;
} server_t_args;

typedef struct {
    int client_fd;
} child_t_args;

void* server_thread(void* args);
void* child_thread(void* args);
// 此函数需要在使用时实现
void handle_message(unsigned char* payload, int* len);

#endif