#ifndef __H_CLIENT__
#define __H_CLIENT__

#define BUFFER_SIZE 1500

#include <netinet/in.h>

typedef struct {
    struct in_addr destination;
    int port;
    unsigned char payload[BUFFER_SIZE];
    int len;
} send_t_args;

void* send_thread(void* args);
// 此函数需要在使用时实现
void handle_response(unsigned char* payload, int* len);

#endif