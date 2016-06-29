#ifndef _H_CLIENT_
#define _H_CLIENT_

#define MYPORT  8887
#define BUFFER_SIZE 1024

typedef void(*POINTER_FUNC)(char*);

void message_handler(char* recv_buffer);
int send_message(int port, char* sendbuf, POINTER_FUNC callback);

#endif