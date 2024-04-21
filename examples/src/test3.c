#include <stdio.h>
#include <stdlib.h>
#include "../../src/ipv4_storage.h"

#define N           150
#define FILEPATH    "examples/addresses.txt"

ipv4_addr_t ipv4_addresses[N];
uint8_t masks[N];

void read_addresses() {
    FILE* fptr = fopen(FILEPATH, "r");

    if (fptr == NULL) {
        printf("no such file.");
        exit(1);
    }


    for (int i=0; i<N; i++) {
        int a, b, c, d, mask;
        fscanf(fptr, "%d %d %d %d %d", &a, &b, &c, &d, &mask);
        ipv4_addresses[i] = (ipv4_addr_t) { .number = ipv4_from_octets((uint8_t)a, (uint8_t)b, (uint8_t)c, (uint8_t)d) };
        masks[i] = (uint8_t)mask;
    }

    fclose(fptr);
}

int main(void) {
    
    read_addresses();

    for (int i=0; i<N; i++) {
        ipv4_addr_t ip = ipv4_addresses[i];
        uint8_t mask = masks[i];

        int res = add(ip.number, mask);
        if (res == -1) {
            printf("[%03d] Couldn't add ipv4 addr %d.%d.%d.%d/%d to the collection.\n", 
                i, ip.octets.a, ip.octets.b, ip.octets.c, ip.octets.d, mask);
        } else {
            printf("[%03d] Added ipv4 addr %d.%d.%d.%d/%d to the collection.\n", 
                i, ip.octets.a, ip.octets.b, ip.octets.c, ip.octets.d, mask);
        }
    }

    _print_tree(NULL, 0, "head");

    return 0;
}