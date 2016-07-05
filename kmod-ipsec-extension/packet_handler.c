#include "packet_handler.h"
#include "message_sender.h"
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/netfilter.h>

int to_eth1(unsigned char* ip)
{
    if (ip[0] == (unsigned char)10)
		if (ip[1] == (unsigned char)1)
			return 1;
	return 0;
}

int from_eth0(unsigned char* ip)
{
    if (ip[0] == (unsigned char)192)
		if (ip[1] == (unsigned char)168)
			if (ip[2] == (unsigned char)0)
				if (ip[3] == (unsigned char)1)
					return 1;
    return 0;
}

int handle_packet(struct socket* sock, unsigned char* iphdr)
{
    if (from_eth0(iphdr+12) == 1 || to_eth1(iphdr+16) == 1) {
        return NF_ACCEPT;
    }
    unsigned char* addrs = (char*)kmalloc(sizeof(char) * 8, GFP_KERNEL);
    memcpy(addrs, iphdr + 12, 8);
    printk("[>] Unknown packet from %d.%d.%d.%d to %d.%d.%d.%d.", IPTRANS(addrs), IPTRANS(addrs + 4));
    printk("\treport\n");
    send_message(sock, addrs, addrs + 4);
    return NF_DROP;
}
