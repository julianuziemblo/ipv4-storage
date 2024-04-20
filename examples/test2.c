#include "../src/ipv4_collection.h"
#include <stdio.h>
#include <stdlib.h>

#define FILEPATH    "examples/addresses.txt"
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
        uint32_t ip_number = ipv4_from_octets((uint8_t)ip.a, (uint8_t)ip.b, (uint8_t)ip.c, (uint8_t)ip.d);
        uint8_t mask = (uint8_t)ip.mask;
        int res = add(ip_number, mask);
        if (res == -1) {
            printf("Address niepoprawny\n");
        }
        // ipv4_addresses[i] = ip;
    }

    printf("descriptor: 0x%p\n", fptr);

    fclose(fptr);
}

int main(void) {
    printf("Sizeof tree node: %lldB\n", sizeof(ipv4_tree_node_t));

    printf("START\n");
    read_addresses();

    // for (int i=0; i<N; i++) {
    //     struct ipv4_addr_t ip = ipv4_addresses[i];
    //     printf("%d. IPv4: = %d.%d.%d.%d/%d\n", i, ip.a, ip.b, ip.c, ip.d, ip.mask);
    //     // int res = add(ipv4_from_octets((uint8_t)ip.a, (uint8_t)ip.b, (uint8_t)ip.c, (uint8_t)ip.d), (uint8_t)ip.mask);
    //     // if (res == -1) {
    //     //     printf("Couldn't add ipv4 addr to the space.\n");
    //     // }
    // }

    // struct ipv4_addr_t ip = ipv4_addresses[47];
    // printf("%d. IPv4: = %d.%d.%d.%d/%d\n", 47, ip.a, ip.b, ip.c, ip.d, ip.mask);
    // uint32_t ip_number = ipv4_from_octets((uint8_t)ip.a, (uint8_t)ip.b, (uint8_t)ip.c, (uint8_t)ip.d);
    // uint8_t mask = (uint8_t)ip.mask;
    // printf("Number: 0x%x, mask: %d\n", ip_number, mask);

    // uint32_t ip_test = ipv4_from_octets(192,0,0,0);
    // printf("IPv4 in number form: 0x%x\n", ip_test);
    // uint8_t mask_test = 18;
    // (void)add(ip_test, mask_test);

    // uint32_t ip_test2 = ipv4_from_octets(128,0,0,0);
    // printf("IPv4 in number form: 0x%x\n", ip_test2);
    // uint8_t mask_test2 = 18;
    // (void)add(ip_test2, mask_test2);

    // // printf("after\n");
    // // _print_tree(get_root(), 0, "head");

    printf("PROGRAM END\n");
    return 0;
}