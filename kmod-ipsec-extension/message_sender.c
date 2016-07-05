#include "message_sender.h"
#include "socket_client.h"
#include "flags.h"
#include <linux/slab.h>

void send_message(struct socket* sock, unsigned char* src, unsigned char* dst)
{
    // dst == src + 4
    struct socket_msg* msg = (struct socket_msg*)kmalloc(sizeof(struct socket_msg), GFP_KERNEL);
    msg->payload = (char*)kmalloc(sizeof(char) * 16, GFP_KERNEL);
    msg->len = 16;
    msg->payload[0] = 0x80;
    msg->payload[1] = 0x00;
    // IDg
    msg->payload[2] = 0x00;
    msg->payload[3] = 0x00;
    msg->payload[4] = 0x00;
    msg->payload[5] = 0x00;
    // NT
    msg->payload[6] = 0x40;
    // event type
    msg->payload[7] = 0x80;
    memcpy(msg->payload+8, src, 8);
    struct socket_msg* rtn = socket_send(sock, msg);
    // printk("return: %d\t", rtn->len);
    // printk("%d %d %d\t", rtn->payload[0], rtn->payload[1], rtn->payload[2]);
    // printk("%d %d %d\n", NOTIFICATION, 0x00, ACK);
    // if (rtn != NULL && rtn->len == 3
    //     && rtn->payload[0] == NOTIFICATION
    //     && rtn->payload[2] == ACK) {
    //     printk("[>] Request accepted.\n");
    // }
}
