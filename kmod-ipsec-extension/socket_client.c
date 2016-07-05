#include "socket_client.h"
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/socket.h>
#include <net/sock.h>
#include <linux/kernel.h>

struct socket_rtn* socket_send(struct socket* sock, struct socket_msg* msg)
{
    int ret = 0;
    struct kvec svec;
    svec.iov_base = msg->payload;
    svec.iov_len = msg->len;
    struct msghdr shdr;
    memset(&shdr, 0, sizeof(shdr));

    ret = kernel_sendmsg(sock, &shdr, &svec, 1, msg->len);
    kfree(msg->payload);
    kfree(msg);
    if (ret < 0) {
        printk("Error: Send message failed.\n");
        return NULL;
    }

    // struct socket_rtn* rtn = (struct socket_rtn*)kmalloc(sizeof(struct socket_rtn), GFP_KERNEL);
    // rtn->payload = (char*)kmalloc(sizeof(char) * SOCK_BUFFER_SIZE, GFP_KERNEL);
    // struct kvec rvec;
    // rvec.iov_base = rtn->payload;
    // rvec.iov_len = SOCK_BUFFER_SIZE;
    // struct msghdr rhdr;
    // memset(&rhdr, 0, sizeof(rhdr));
    // rtn->len = kernel_recvmsg(sock, &rhdr, &rvec, 1, SOCK_BUFFER_SIZE, 0);
    return NULL;
}

struct socket* kie_socket_init(struct socket_addr* saddr)
{
    struct socket* sock;
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = saddr->dst_port;
    s_addr.sin_addr.s_addr = saddr->dst_ip.s_addr;
    kfree(saddr);

    sock = (struct socket*)kmalloc(sizeof(struct socket), GFP_KERNEL);
    int ret = 0;
    ret = sock_create_kern(AF_INET, SOCK_STREAM, 0, &sock);
    if (ret < 0) {
        printk("Error: Create socket failed.\n");
        return NULL;
    }

    ret = sock->ops->connect(sock, (struct sockaddr*)&s_addr, sizeof(s_addr), 0);
    if (ret != 0) {
        printk("Error: Connect to server failed.\n");
        return NULL;
    }
    return sock;
}

void kie_socket_exit(struct socket* sock)
{
    if (sock != NULL) {
        sock_release(sock);
    }
}
