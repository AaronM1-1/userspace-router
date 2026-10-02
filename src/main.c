#include "../include/ethernet.h"
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>


int main() {
    
    int socket_fd = eth_initialize();

    unsigned char buff[2048];
    struct eth_header eHeader;
    
    while(1) {
        ssize_t bytesRecv = eth_receive(socket_fd, buff, sizeof(buff));
        if(bytesRecv == -1) {
            printf("Main error");
            continue;
        }
        if(bytesRecv == -2) {
            printf("Try again");
            continue;
        }

        int parseStatus = eth_parse(buff, bytesRecv, &eHeader);
        if(parseStatus == -1) {
            continue;
        }

        switch(ntohs(eHeader.ethType)) {
            case ETH_P_IP:
                //process ipv4
                break;
            case ETH_P_ARP:
                //process arp
                break;
            case ETH_P_IPV6:
                //process ipv6
                break;
            default:
                break;
        }
    }

    close(socket_fd);

}

