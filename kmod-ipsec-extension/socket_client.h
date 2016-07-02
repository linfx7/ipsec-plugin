#ifndef __H_SOCKET_CLIENT__
#define __H_SOCKET_CLIENT__

#include <linux/in.h>
#include <net/sock.h>

#define SOCK_BUFFER_SIZE 128

struct socket_addr {
    struct in_addr dst_ip;
    unsigned short dst_port;
};

struct socket_msg {
    unsigned char* payload;
    unsigned int len;
};

struct socket_rtn* socket_send(struct socket*, struct socket_msg*);
struct socket* kie_socket_init(struct socket_addr*);
void kie_socket_exit(struct socket*);

#endif