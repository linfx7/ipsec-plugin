#include "server_callback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* message_handler(char* recv_buffer)
{
    //handle message
    fputs(recv_buffer, stdout);
    recv_buffer[strlen(recv_buffer)-1] = '\0';
    strcat(recv_buffer, " has been handled!\n");
    fputs(recv_buffer, stdout);
    return recv_buffer;
}