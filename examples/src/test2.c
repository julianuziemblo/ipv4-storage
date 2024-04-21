#include "../../src/ipv4_storage.h"
#include <stdio.h>
#include <stdlib.h>

#define FILEPATH    "examples/prefixes.txt"
#define N           100

struct ipv4_addr_t {
    int a, b, c, d, mask;
} ipv4_addresses[N];

void read_addresses() {
    FILE* fptr = fopen(FILEPATH, "r");

    if (fptr == NULL) {
        printf("no such file.");
        exit(1);
    }

    struct ipv4_addr_t ip;

    for (int i=0; i<N; i++) {
        fscanf(fptr, "%d %d %d %d %d", &ip.a, &ip.b, &ip.c, &ip.d, &ip.mask);
        ipv4_addresses[i] = ip;
    }

    fclose(fptr);
}

int main(void) {
    printf("START\n");
    read_addresses();

    for (int i=0; i<N; i++) {
        struct ipv4_addr_t ip = ipv4_addresses[i];
        // printf("%d. IPv4: = %d.%d.%d.%d/%d\n", i, ip.a, ip.b, ip.c, ip.d, ip.mask);
        int res = add(ipv4_from_octets((int8_t)ip.a, (int8_t)ip.b, (int8_t)ip.c, (int8_t)ip.d), (int8_t)ip.mask);
        if (res == -1) {
            printf("Couldn't add ipv4 addr to the collection.\n");
        }
    }

    _print_tree(NULL, 0, "head");

    printf("PROGRAM END\n");
    return 0;
}