#ifndef   _H_SERVER_
#define  _H_SERVER_

#define MYPORT  8887
#define QUEUE   20
#define BUFFER_SIZE 1024

typedef char*(*POINTER_FUNC)(char*);
typedef struct thread_info
{
    int port_or_conn;
    POINTER_FUNC callback;
}THREAD_INFO;

void* thread(void* cac);
void* server_thread(void* poc);

#endif