#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdint.h>

struct eth_header {
    char destAddress[6];
    char sourceAddress[6];
    uint16_t ethType;
};


#endif

