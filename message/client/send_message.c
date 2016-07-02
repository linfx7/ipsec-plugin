#include "client.h"
#include "../flags.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

void handle_response(unsigned char* payload, int* len)
{
    if (*len == 3 && payload[0] == NOTIFICATION) {
        if (payload[2] != ACK) {
            perror("Error: Notification send failed.");
        } else {
            printf("ACK\n");
        }
    }
}

void send_message(send_t_args args)
{
    // send_thread(&args);
    int i;
    for (i = 0; i < 2; ++i) {
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, send_thread, &args) != 0) {
            perror("Error: Create send thread failed.");
            exit(1);
        }
    }
    // pthread_join(thread_id, &rtn);
}

// int main()
// {
//     while(1){}
    /*
    // send_t_args args;
    args.destination.s_addr = inet_addr("219.224.168.138");
    args.port = htons(1919);
    unsigned char add[] = {0x10, 0x01, 0x10, 0x11, 0x10, 0x01, 0x10, 0x01};    
    unsigned char payload[16];
    // HDR
    payload[0] = NOTIFICATION;
    payload[1] = 0x00;
    // IDg
    payload[2] = 0x00;
    payload[3] = 0x00;
    payload[4] = 0x00;
    payload[5] = 0x00;
    // NT
    payload[6] = EVENT;
    // event type
    payload[7] = EVENT_PACKET;
    // src
    payload[8] = add[0];
    payload[9] = add[1];
    payload[10] = add[2];
    payload[11] = add[3];
    // dst
    payload[12] = add[4];
    payload[13] = add[5];
    payload[14] = add[6];
    payload[15] = add[7];
    args.payload = payload;
    args.len = 16;
    printf("start\n");
    send_message(args);
    printf("finish\n"); */
//     return 0;
// }