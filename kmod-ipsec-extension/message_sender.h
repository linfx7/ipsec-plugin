#ifndef __H_MESSAGE_SENDER__
#define __H_MESSAGE_SENDER__

#include <net/sock.h>

void send_message(struct socket*, unsigned char* src, unsigned char* dst);

#endif
