#include "packet_handler.h"
#include "message_sender.h"
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/netfilter.h>

static unsigned char buffer[3000][8];
static int total = 0, position = 0;

int equals(unsigned char* a, unsigned char* b, int len)
{
    int i;
    for (i = 0; i < len; ++i) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int handle_packet(struct socket* sock, unsigned char* iphdr)
{
    int i;
    for (i = 0; i < total; ++i) {
        if (equals((iphdr + 12), buffer[i], 8))
            return NF_DROP;
    }

    memcpy(buffer[position], iphdr + 12, 8);
    position = (position+1)%3000;
    if (total < 3000) {
        total++;
    }

    printk("[>] Unknown packet from %d.%d.%d.%d to %d.%d.%d.%d.\n", IPTRANS(iphdr + 12), IPTRANS(iphdr + 16));
    if (sock != NULL) {
        send_message(sock, iphdr + 12, iphdr + 16);
    }
    return NF_DROP;
}
