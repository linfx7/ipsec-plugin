#include "client.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* send_thread(void* args)
{
    printf("pos1\n");
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Error: Get socket failed.");
        exit(1);
    }
    send_t_args c_args = *((send_t_args*)args);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = c_args.destination.s_addr;
    server_addr.sin_port = c_args.port;

    printf("pos2\n");
    // 连接服务器，成功返回0，错误返回-1
    if (connect(client_fd, (struct sockaddr*)&server_addr,
                sizeof(server_addr))) {
        perror("Error: Connect to server failed.");
        close(client_fd);
    }

    printf("pos3\n");
    if (c_args.len > 0) {
        // 发送消息
        unsigned char buffer[BUFFER_SIZE]; 
        send(client_fd, c_args.payload, c_args.len, 0);
        int len = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (len > 0) {
            handle_response(buffer, &len);
        }
    }
    printf("pos4\n");
    close(client_fd);
    return 0;
}