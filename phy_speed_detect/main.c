#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/sockios.h>
#include <linux/if.h>
#include <linux/ethtool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define ETH0_NAME "eth0"

int get_link_status(char *dev)
{
    int sock, rc, link = 0;
    struct ifreq ifr;
    struct ethtool_value evalue;

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    strncpy(ifr.ifr_name, dev, sizeof(ifr.ifr_name));

    evalue.cmd = ETHTOOL_GLINK;
    ifr.ifr_data = (caddr_t)&evalue;
    rc = ioctl(sock, SIOCETHTOOL, &ifr);

    if (rc < 0) {
        perror("ioctl");
        close(sock);
        exit(1);
    }

    link = evalue.data;
    switch (link) {
    case 0:
        printf("CABLE DOWN\n");
        break;
    case 1:
        printf("UP\n");
        break;
    default:
        printf("UNKNOWN\n");
        link = -1;
        break;
    }
    close(sock);
    return link;
}

int main (int argc, char **argv)
{
    int sock;
    struct ifreq ifr;
    struct ethtool_cmd edata;
    int rc;


    if (get_link_status(ETH0_NAME)) {

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    strncpy(ifr.ifr_name, ETH0_NAME, sizeof(ifr.ifr_name));



    ifr.ifr_data = &edata;
    edata.cmd = ETHTOOL_GSET;
    rc = ioctl(sock, SIOCETHTOOL, &ifr);
    if (rc < 0) {
        perror("ioctl");
        close(sock);
        exit(1);
    }

    switch (ethtool_cmd_speed(&edata)) {
    case SPEED_10:
            sleep(1);
            if (1 == get_link_status(ETH0_NAME))
                printf("10Mbps\n");
            else
                printf("DOWN\n");
            break;

    case SPEED_100: printf("100Mbps\n"); break;
    case SPEED_1000: printf("1Gbps\n"); break;
    default: printf("Speed returned is %d\n", edata.speed);
    }

    } else {
            printf("%s: DOWN\n", __func__);
    }
    close(sock);
    return (0);
}
