#include <sys/socket.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include "../include/ethernet.h"
#include <errno.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>


int eth_initialize(void) {
    struct sockaddr_ll bind_addr = {0};
    bind_addr.sll_family = AF_PACKET;
    bind_addr.sll_ifindex = if_nametoindex("enp4s0");
    bind_addr.sll_protocol = htons(ETH_P_ALL);

    int socket_packet;
    if((socket_packet = socket(AF_PACKET, SOCK_RAW, bind_addr.sll_protocol)) == -1) {
        fprintf(stderr, "Socket Error: %s\n", strerror(errno));
        exit(1);
    }
    
    if(bind(socket_packet, (struct sockaddr*)&bind_addr, sizeof(bind_addr)) == -1) {
        fprintf(stderr, "Bind Error: %s\n", strerror(errno));
        exit(1);
    }
    
    return socket_packet;
}


ssize_t eth_receive(int socket_fd, unsigned char* buff, int len) {
    int dataRecv;
    struct sockaddr_ll recv_addr = {0};
    socklen_t addLen = sizeof(recv_addr);
    if((dataRecv = recvfrom(socket_fd, buff, len, 0, (struct sockaddr *)&recv_addr, &addLen)) == -1) {
        if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
            return -2;
        } else {
            fprintf(stderr, "recvfrom error: %s\n" , strerror(errno));
            return -1;
        }
    }

    return dataRecv;
}

int eth_parse(unsigned char* buff, int bytesRecv, struct eth_header* e) {
    if(bytesRecv >= 14) {
        memcpy(e->destAddress, buff, 6);
        memcpy(e->sourceAddress, buff+6, 6);
        memcpy(&e->ethType, buff+12, 2);
        return 0;
    } else {
        return -1;
    }
}
