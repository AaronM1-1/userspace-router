#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>
#include <stdlib.h>


struct eth_header {
    unsigned char destAddress[6];
    unsigned char sourceAddress[6];
    uint16_t ethType;
};

int eth_initialize(void);
ssize_t eth_receive(int socket_fd, char* buff, int len);
int eth_parse(unsigned char* buff, int len, struct eth_header* e);

#endif

