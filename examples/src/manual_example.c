#include "../../src/ipv4_storage.h"
#include <stdio.h>

#define LOOP for(;;)

void handle_add() {
    int a, b, c, d, m;
    printf("IPv4 prefix (CIDR notation): ");
    fflush(stdout);
    scanf(" %d.%d.%d.%d/%d", &a, &b, &c, &d, &m);
    fflush(stdout);
    
    uint32_t prefix = ipv4_from_octets((uint8_t)a, (uint8_t)b, (uint8_t)c, (uint8_t)d);
    int8_t mask = (int8_t)m;
    printf("Preparing to add IPv4 prefix to the collection: ");
    ipv4_prefix_print(prefix, mask);

    int add_res = add(prefix, mask);
    if (add_res == -1) {
        printf("Bad IPv4 prefix: ");
    } else {
        printf("Added (if it didn't exist) IPv4 prefix: ");
    }
    ipv4_prefix_print(prefix, mask);
}

void handle_del() {
    int a, b, c, d, m;
    printf("IPv4 prefix (CIDR notation): ");
    fflush(stdout);
    scanf(" %d.%d.%d.%d/%d", &a, &b, &c, &d, &m);
    fflush(stdout);
    
    uint32_t prefix = ipv4_from_octets((uint8_t)a, (uint8_t)b, (uint8_t)c, (uint8_t)d);
    int8_t mask = (int8_t)m;
    printf("Prepering to delete IPv4 prefix from the collection: ");
    ipv4_prefix_print(prefix, mask);

    int del_res = del(prefix, mask);
    if (del_res == -1) {
        printf("Couldn't delete IPv4 prefix from the collection: ");
    } else {
        printf("Deleted (if existed) IPv4 prefix: ");
    }
    ipv4_prefix_print(prefix, mask);
}

void handle_check() {
    int a, b, c, d;
    printf("IPv4 address: ");
    fflush(stdout);
    scanf(" %d.%d.%d.%d", &a, &b, &c, &d);
    fflush(stdout);
    
    uint32_t prefix = ipv4_from_octets((uint8_t)a, (uint8_t)b, (uint8_t)c, (uint8_t)d);
    printf("Preparing to check if IPv4 address is in the collection: ");
    ipv4_print(prefix);

    int8_t check_res = check(prefix);
    if (check_res == -1) {
        printf("IPv4 address not found in the collection: ");
    } else {
        printf("Found IPv4 address in the collection, (mask: %d): ", check_res);
    }
    ipv4_print(prefix);
}

int main(void) {
    printf("#### MANUAL EXAMPLE ####\n\n");
    int opt;
    LOOP {
        printf("What would you like to do?\n");
        printf(" 1. Add prefix to the tree.\n");
        printf(" 2. Delete prefix from the tree.\n");
        printf(" 3. Check, if IPv4 address is in the tree.\n");
        printf(" 4. Free unused nodes.\n");
        printf(" 5. Exit.\n\n");
        
        fflush(stdout);

        scanf("%d", &opt);
        switch(opt) {
            case 1:
                handle_add();
                break;
            case 2:
                handle_del();
                break;
            case 3:
                handle_check();
                break;
            case 4:
                free_unused();
                break;
            case 5:
                return 0;
            default:
                printf("Provided unknown option: %d\n", opt);
                break;
        }
        
        printf("Tree size: %lld\n", size());
        printf("Nodes allocated: %lld (%lld B)\n\n", allocated_nodes(), allocated_nodes() * sizeof(ipv4_tree_node_t));
    }

    return 0;
}
