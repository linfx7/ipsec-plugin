#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* server_thread(void* args)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error: Get socket failed.");
        exit(1);
    }
    server_t_args s_args = *((server_t_args*)args);

    // 定义sockaddr_in
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(s_args.port);

    // bind，成功为0，出错为-1
    if (bind(server_fd, (struct sockaddr*)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("Error: Bind failed.");
        close(server_fd);
        exit(1);
    }

    // listen，成功返回0，出错返回-1
    if (listen(server_fd, 10) == -1) {
        perror("Error: Listen failed.");
        close(server_fd);
        exit(1);
    }

    while (1) {
        // Accept客户端
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(struct sockaddr_in);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr,
                               &client_addr_len);
        if (client_fd < 0) {
            perror("Error: Accept failed.");
            close(server_fd);
            exit(1);
        }
        printf("Msg: Accept client %d.\n", client_fd);

        // 创建Child Thread处理消息
        pthread_t thread_id;
        child_t_args c_args = { client_fd };
        if (pthread_create(&thread_id, NULL, child_thread, &c_args) != 0) {
            perror("Error: Create child thread failed.");
            close(server_fd);
            exit(1);
        }
    }
    // 关闭服务器
    close(server_fd);
}

void* child_thread(void* args)
{
    child_t_args c_args = *((child_t_args*)args);
    unsigned char buffer[BUFFER_SIZE];
    int len = recv(c_args.client_fd, buffer, BUFFER_SIZE, 0);
    if (len > 0) {
        handle_message(buffer, (int*)&len);
        send(c_args.client_fd, buffer, len, 0);
    }
    close(c_args.client_fd);
    return NULL;
}