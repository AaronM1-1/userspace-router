#ifndef ARP_H
#define ARP_H

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

struct arp_header {
    uint16_t operation; 
    unsigned char senderMac[6];
    unsigned char sendIP[4];
    unsigned char targetIP[4];
    unsigned char targetMac[6];
};

struct arp_cache_entry {
    unsigned char mac[6];
    unsigned char ip[4];
    bool flag;
    time_t last_used;
};

int arp_parse(unsigned char* buff, ssize_t len);
int arp_operation(uint16_t op);

#endif
