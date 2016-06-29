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
#include "client.h"

int main()
{
    char sendbuf[BUFFER_SIZE];
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send_message(MYPORT,sendbuf,message_handler);
    }
    return 0;
}
void message_handler(char* recv_buffer)
{
    //handle message
    fputs(recv_buffer, stdout);
    char* result = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    memset(result, 0, sizeof(char)*BUFFER_SIZE);
    strcpy(result,"client has handled the message!\n");
    fputs(result, stdout);
}

int send_message(int port, char* sendbuf, POINTER_FUNC callback)
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip

    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char recvbuf[BUFFER_SIZE];
    if (sendbuf != NULL)
     {
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
        int len = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
        if (len <= 0)
        {
            perror("recv");
            return -1;
        }
        callback(recvbuf);

        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
     }

    close(sock_cli);
    return 0;
}