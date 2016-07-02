#include "packet_handler.h"
#include "message_sender.h"
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/inet.h>
#include <linux/in.h>

void handle_packet(struct socket* sock, unsigned char* iphdr)
{
    unsigned char* addrs = (char*)kmalloc(sizeof(char) * 8, GFP_KERNEL);
    memcpy(addrs, iphdr + 12, 8);

    printk("[>] Unknown packet from %d.%d.%d.%d to %d.%d.%d.%d.", IPTRANS(addrs), IPTRANS(addrs + 4));
    if ((not_controller(addrs) == 0) && (not_controller(addrs+4) == 0)) {
        printk("\treport\n");
        send_message(sock, addrs, addrs + 4);
    } else {
        printk("\tnothing\n");
    }
}

int not_controller(unsigned char* ip)
{
    if (ip[0] != (unsigned char)219) return 0;
    if (ip[1] != (unsigned char)224) return 0;
    if (ip[2] != (unsigned char)168) return 0;
    if (ip[3] != (unsigned char)138) return 0;

    return 1;
}
