#include <stdio.h>
#include "../include/arp.h"
#include <string.h>
#include <stdbool.h>

static struct arp_cache_entry arpTable[64];

int arp_parse(unsigned char* buff, ssize_t len) {
    if(len < 28) {
        return -1;
    }
    
    struct arp_header arpHeader;
    struct arp_cache_entry entry;

    memcpy(&arpHeader.operation, buff+6, 2);
    memcpy(arpHeader.senderMac, buff+8, 6);
    memcpy(arpHeader.sendIP, buff+14, 4);
    memcpy(arpHeader.targetMac, buff+18, 6);
    memcpy(arpHeader.targetIP, buff+24, 4);
    memcpy(entry.mac, buff+8, 6);
    memcpy(entry.ip, buff+14, 4);

    time_t largestUnused = 0;
    int index = 0;
    time_t t = time(NULL);

    for(int i = 0; i < 64; i++) {
        if(((memcmp(entry.ip, arpTable[i].ip, 4)) == 0) && (arpTable[i].flag)) {
            memcpy(arpTable[i].mac, arpHeader.senderMac, 6);
            arpTable[i].last_used = t;
            break;
        }

        if(arpTable[i].flag == false) {
            memcpy(arpTable[i].ip, entry.ip, 4);
            memcpy(arpTable[i].mac, entry.mac, 6);
            arpTable[i].flag = true;
            arpTable[i].last_used = t;
            break;
        }

        if(largestUnused < (t - arpTable[i].last_used)) {
            largestUnused = t - arpTable[i].last_used;
            index = i;
        }

        if(i == 63 && (arpTable[i].flag == true)) {
            //table is full replace the entry with the longest time in last used with the new entry. now - lastused
            memcpy(arpTable[index].ip, entry.ip, 4);
            memcpy(arpTable[index].mac, entry.mac, 6);
            arpTable[index].flag = true;
            arpTable[index].last_used = t;
            break;
        }
    }
        
    return 0;
}

int arp_operation(uint16_t op) {

}

