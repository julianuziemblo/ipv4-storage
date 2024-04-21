#include "../../src/ipv4_storage.h"
#include <stdio.h>

int main(void) {
    printf("#### SMALL OPERATIONS EXAMPLE ####\n\n");

    uint32_t ip1 = ipv4_from_octets(192,0,24,0);
    int8_t mask1 = 9;
    printf("First prefix: ");
    ipv4_prefix_print(ip1, mask1);
    int add_res1 = add(ip1, mask1);
    printf("is it valid: %s\n", add_res1 == -1 ? "no" : "yes");
    printf("current tree size: %lld\n\n", size());

    uint32_t ip2 = ipv4_from_octets(127,0,0,0);
    int8_t mask2 = 9;
    printf("Second prefix: ");
    ipv4_prefix_print(ip2, mask2);
    int add_res2 = add(ip2, mask2);
    printf("is it valid: %s\n", add_res2 == -1 ? "no" : "yes");
    printf("current tree size: %lld\n\n", size());

    uint32_t ip3 = ipv4_from_octets(10,128,9,1);
    int8_t mask3 = 32;
    printf("Third prefix: ");
    ipv4_prefix_print(ip3, mask3);
    int add_res3 = add(ip3, mask3);
    printf("is it valid: %s\n", add_res3 == -1 ? "no" : "yes");
    printf("current tree size: %lld\n\n", size());

    uint32_t ip4 = ipv4_from_octets(127,0,0,1);
    printf("IPv4 address: ");
    ipv4_print(ip4);
    int8_t check_res1 = check(ip4);
    printf("is it contained in the tree: %s\n", check_res1 == -1 ? "no" : "yes");
    if (check_res1 != -1)
        printf("\tbiggest mask: %d\n\n", check_res1);
    else printf("\n");

    printf("Deleting second prefix: ");
    ipv4_prefix_print(ip2, mask2);
    int del_res = del(ip2, mask2);
    printf("was it deleted: %s\n", del_res == -1 ? "no" : "yes");
    printf("current tree size: %lld\n\n", size());

    printf("IPv4 address: ");
    ipv4_print(ip4);
    int8_t check_res2 = check(ip4);
    printf("is it contained in the tree: %s\n", check_res2 == -1 ? "no" : "yes");
    if (check_res2 != -1)
        printf("\tbiggest mask: %d\n\n", check_res2);
    else printf("\n");

    return 0;
}