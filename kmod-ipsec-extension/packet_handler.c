#include "packet_handler.h"
#include "message_sender.h"
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/netfilter.h>

int handle_packet(struct socket* sock, unsigned char* iphdr)
{
    printk("[>] Unknown packet from %d.%d.%d.%d to %d.%d.%d.%d.\n", IPTRANS(iphdr+12), IPTRANS(iphdr+16));
    if (sock != NULL)
        send_message(sock, iphdr+12, iphdr+16);
    return NF_DROP;
}
