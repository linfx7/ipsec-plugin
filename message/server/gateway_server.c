#include "server.h"
#include "../flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void handle_message(char* payload, int* len)
{
    //handle message
    // fputs(recv_buffer, stdout);
    // recv_buffer[strlen(recv_buffer)-1] = '\0';
    // strcat(recv_buffer, " has been handled!\n");
    // fputs(recv_buffer, stdout);
    // return recv_buffer;
}

void init_server(server_t_args args) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, server_thread, &args) != 0) {
        perror("Error: Create server thread failed.");
        exit(1);
    }
}