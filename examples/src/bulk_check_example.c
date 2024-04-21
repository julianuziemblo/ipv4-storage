#include <stdio.h>
#include <stdlib.h>
#include "../../src/ipv4_storage.h"

#define PREFIXES_PATH   "examples/prefixes.txt"
#define ADDRESSES_PATH  "examples/addresses.txt"

#define PREFIXES_LEN    100
#define ADDRESSES_LEN   40

void read_addresses(const char* filepath, uint32_t* ips, int8_t* masks, size_t data_len) {
    FILE* fptr = fopen(filepath, "r");

    if (fptr == NULL) {
        printf("ERROR: no such file `%s`\n", filepath);
        exit(1);
    }

    for (int i=0; i<data_len; i++) {
        int a, b, c, d, mask;
        fscanf(fptr, "%d %d %d %d  %d", &a, &b, &c, &d, &mask);
        ips[i] = ipv4_from_octets((uint8_t)a, (uint8_t)b, (uint8_t)c, (uint8_t)d);
        masks[i] = (int8_t)mask;
    }

    fclose(fptr);
}

int main(void) {
    uint32_t prefixes[PREFIXES_LEN];
    int8_t   masks[PREFIXES_LEN];
    read_addresses(PREFIXES_PATH, prefixes, masks, PREFIXES_LEN);

    uint32_t addresses[ADDRESSES_LEN];
    int8_t   _[ADDRESSES_LEN];
    read_addresses(ADDRESSES_PATH, addresses, _, ADDRESSES_LEN);
    (void)_;

    printf("#### BULK CHECK() EXAMPLE ####\n");
    printf("Expected: the first 20 IPv4 addresses should be contained in the tree, the last 20 - shouldn't.\n\n");

    // Add all prefixes to the tree
    for (int i=0; i<PREFIXES_LEN; i++) {
        int add_res = add(prefixes[i], masks[i]);
        (void)add_res;
        // if (add_res == -1) {
        //     printf("[%03d] Couldn't add IPv4 prefix to the collection: ", i+1);
        // } else {
        //     printf("[%03d] Added IPv4 prefix to the collection: ", i+1);
        // }
        // ipv4_prefix_print(prefixes[i], masks[i]);
    }

    // Check, which addresses are contained in the tree
    for (int i=0; i<ADDRESSES_LEN; i++) {
        int8_t check_res = check(addresses[i]);
        if (check_res == -1) {
            printf("[%02d] Address not found in the tree: ", i+1);
        } else {
            printf("[%02d] Address found in the tree with biggest mask %d: ", i+1, check_res);
        }
        ipv4_print(addresses[i]);
    }

    return 0;
}