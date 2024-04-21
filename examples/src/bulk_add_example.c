#include <stdio.h>
#include <stdlib.h>
#include "../../src/ipv4_storage.h"

#define N           100
#define FILEPATH    "examples/prefixes.txt"

uint32_t ips[N];
int8_t masks[N];

void read_addresses() {
    FILE* fptr = fopen(FILEPATH, "r");

    if (fptr == NULL) {
        printf("no such file.");
        exit(1);
    }


    for (int i=0; i<N; i++) {
        int a, b, c, d, mask;
        fscanf(fptr, "%d %d %d %d %d", &a, &b, &c, &d, &mask);
        ips[i] = ipv4_from_octets(a, b, c, d);
        masks[i] = (int8_t)mask;
    }

    fclose(fptr);
}

int main(void) {
    
    read_addresses();

    printf("#### BULK ADD() EXAMPLE ####\n");
    printf("Expected: all prefixes are valid and unique, therefore all should be added to the tree.\n\n");

    for (int i=0; i<N; i++) {
        uint32_t ip = ips[i];
        int8_t mask = masks[i];

        int res = add(ip, mask);
        if (res == -1) {
            printf("[%03d] Couldn't add IPv4 prefix to the collection: ", i+1);
        } else {
            printf("[%03d] Added IPv4 prefix to the collection: ", i+1);
        }
        ipv4_prefix_print(ip, mask);
    }

    printf("\nAdded prefixes: %lld\n", size());
    printf("Allocated nodes: %lld (%lld B)\n", allocated_nodes(), allocated_nodes() * sizeof(ipv4_tree_node_t));

    return 0;
}