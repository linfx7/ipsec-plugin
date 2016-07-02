#include <linux/netlink.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NETLINK_IPSEC_EXT 17
#define NL_GROUP 2
#define IPTRANS(addr) ((unsigned char*)(addr))[0], \
                      ((unsigned char*)(addr))[1], \
                      ((unsigned char*)(addr))[2], \
                      ((unsigned char*)(addr))[3]

int init_netlink() {
    int sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_IPSEC_EXT);
    if (sock < 0) {
        perror("Error: Get netlink socket failed.");
        exit(1);
    }
    struct sockaddr_nl saddr;
    memset((void*)&saddr, 0, sizeof(saddr));
    saddr.nl_family = AF_NETLINK;
    saddr.nl_groups = NL_GROUP;
    saddr.nl_pid = getpid();

    if (bind(sock, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        perror("Error: Bind socket failed.");
        exit(1);
    }
    return sock;
}

char* get_msg(int sock)
{
    char buffer[8];
    struct sockaddr_nl nladdr;
    struct nlmsghdr nlh;
    struct msghdr msg;
    struct iovec iov;
    iov.iov_base = (void*)&nlh;
    iov.iov_len = sizeof(nlh);
    msg.msg_name = (void*)&nladdr;
    msg.msg_namelen = sizeof(nladdr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    int rtn = recvmsg(sock, &msg, 0);
    if (rtn < 0) {
        perror("Error: Receive message failed.");
        exit(1);
    }
    char* rlt = (char*)malloc(sizeof(char)*8);
    memcpy(rlt, NLMSG_DATA(&nlh), 8);
    return rlt;
}

int main()
{
    int sock = init_netlink();
    init_netlink();
    return 0;
    while(1) {
        char* msg = get_msg(sock);
        // printf("%d.%d.%d.%d\n", IPTRANS(msg), IPTRANS(msg+4));
        printf("%s\n", msg);
    }
}