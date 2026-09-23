#include <sys/socket.h>
#include <linux/if_packet.h>
#include <netinet/in.h>
#include "../include/ethernet.h"
#include <errno.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>

int main() {
    
    struct sockaddr_ll addr = {0};
    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = if_nametoindex("enp4s0");
    addr.sll_protocol = htons(ETH_P_ALL);

    int socket_packet;
    if((socket_packet = socket(AF_PACKET, SOCK_RAW, addr.sll_protocol)) == -1) {
        fprintf(stderr, "Socket Error: %s\n", strerror(errno));
        exit(1);
    }
   
    if(bind(socket_packet, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Bind Error: %s\n", strerror(errno));
        exit(1);
    }

    
    unsigned char buff[2048];
    socklen_t addLen = sizeof(addr);
    int dataRecv = 0;
    if((dataRecv = recvfrom(socket_packet, buff, sizeof(buff), 0, (struct sockaddr *)&addr, &addLen)) == -1) {
        fprintf(stderr, "Recv Error: %s\n", strerror(errno));
        exit(1);
    }

    
    for(int i = 0; i < dataRecv; i++) {
        printf("%02x ", buff[i]);
    }
    printf("\n");
   
    close(socket_packet);
}
