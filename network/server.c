#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include "server.h"
#include "server_callback.h"


void* thread(void* cac)
{
    THREAD_INFO ti = *((THREAD_INFO*)cac);
    int conn = ti.port_or_conn;
    POINTER_FUNC callback = ti.callback;
    char recv_buffer[BUFFER_SIZE];

    while(1)
    {
        memset(recv_buffer,0,sizeof(recv_buffer));
        int len = recv(conn, recv_buffer, sizeof(recv_buffer),0);
        if (len <= 0)
        {
            printf("%s %d %s\n","thread",conn,"exit!" );
            break;
        }
        callback(recv_buffer);
        send(conn,recv_buffer,strlen(send_buffer),0); 
        memset(recv_buffer,0,sizeof(recv_buffer));
    }
    close(conn);
    pthread_exit(NULL);
}

void* server_thread(void* poc)
{
    THREAD_INFO ti = *((THREAD_INFO*)poc);
    int sin_port = ti.port_or_conn;
    POINTER_FUNC callback = ti.callback;    
     ///定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(sin_port);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }

    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    while(1)
    {
         ///客户端套接字
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

         ///成功返回非负描述字，出错返回-1
        int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
        if(conn<0)
        {
            perror("connect");
            continue;
        }
        ///create thread
        pthread_t thread_id;
        THREAD_INFO cac = {conn,callback};
        if (pthread_create(&thread_id, NULL, thread, &cac)!=0)
        {
            perror("pthread_create client");
            break;
        }
        pthread_join(thread_id,NULL);
    }

    close(server_sockfd);
}

int main()
{
    int port = MYPORT;
    THREAD_INFO poc = {port,message_handler};
    pthread_t server_thread_id;
    if (pthread_create(&server_thread_id,NULL,server_thread,&poc)!=0)
    {
        perror("server_thread create!");
    }
    pthread_join(server_thread_id,NULL);
    return 0;
}