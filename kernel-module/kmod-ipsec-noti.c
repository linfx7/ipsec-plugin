#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

#define IPTRANS(addr) ((unsigned char *)(addr))[0], ((unsigned char *)(addr))[1], ((unsigned char *)(addr))[2], ((unsigned char *)(addr))[3]  

#define NF_IP_PRE_ROUTING	0
#define NF_IP_LOCAL_IN		1
#define NF_IP_FORWARD		2
#define NF_IP_LOCAL_OUT		3
#define NF_IP_POST_ROUTING	4
#define NF_IP_NUMHOOKS		5

MODULE_LICENSE("GPL");
MODULE_AUTHOR("linfx7");
MODULE_DESCRIPTION("IPsec packet notification");

// enum {
//     NF_IP_PRE_ROUTING,
//     NF_IP_LOCAL_IN,
//     NF_IP_FORWARD,
//     NF_IP_LOCAL_OUT,
//     NF_IP_POST_ROUTING,
//     NF_IP_NUMHOOKS
// };

static struct nf_hook_ops in_nfho; //net filter hook option struct
static struct nf_hook_ops out_nfho; //net filter hook option struct

unsigned int notification_hook(unsigned int hooknum,
        struct sk_buff* skb,
        const struct net_device* in,
        const struct net_device* out,
        int (*okfn)(struct sk_buff*))
{
    unsigned char* iphdr = skb_network_header(skb);
    if (iphdr)
    {
        printk("[>] Packet from %d.%d.%d.%d to %d.%d.%d.%d.\n", IPTRANS(iphdr + 12), IPTRANS(iphdr + 16));
    }
    return NF_ACCEPT;
}

static void init_filter_if(void)
{
    //NF_IP_PRE_ROUTING hook
    in_nfho.hook = notification_hook;
    in_nfho.hooknum = NF_IP_PRE_ROUTING;
    in_nfho.pf = PF_INET;
    in_nfho.priority = NF_IP_PRI_FIRST;

    nf_register_hook(&in_nfho);

    //NF_IP_LOCAL_OUT hook
    out_nfho.hook = notification_hook;
    out_nfho.hooknum = NF_IP_LOCAL_OUT;
    out_nfho.pf = PF_INET;
    out_nfho.priority = NF_IP_PRI_FIRST;

    nf_register_hook(&out_nfho);
}

// 
static int notification_init(void)
{
    printk(KERN_INFO "[+] Install IPsec Notification module!\n");
    init_filter_if();
    return 0; // Non-zero return means that the module couldn't be loaded.
}

static void notification_exit(void)
{
    nf_unregister_hook(&in_nfho);
    nf_unregister_hook(&out_nfho);
    printk(KERN_INFO "[-] Remove up IPsec Notification module.\n");
}

module_init(notification_init);
module_exit(notification_exit);
