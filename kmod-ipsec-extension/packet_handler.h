#ifndef __H_PACKET_HANDLER__
#define __H_PACKET_HANDLER__

#include <net/sock.h>

#define IPTRANS(addr) ((unsigned char*)(addr))[0], \
                      ((unsigned char*)(addr))[1], \
                      ((unsigned char*)(addr))[2], \
                      ((unsigned char*)(addr))[3]

int handle_packet(struct socket*, unsigned char*);

#endif
