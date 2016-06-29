#include "client.h"
#include "../flags.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void handle_response(unsigned char* payload, int* len)
{
    if (*len == 3 && payload[0] == NOTIFICATION) {
        if (payload[2] != ACK) {
            perror("Error: Notification send failed.");
        }
    }
}

void send_message(send_t_args args)
{
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, send_thread, &args) != 0) {
        perror("Error: Create send thread failed.");
        exit(1);
    }
}