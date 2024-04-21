#include "../../src/ipv4_storage.h"
#include <stdio.h>

int main(void) {
    uint32_t ip = ipv4_from_octets(192,0,24,0);
    uint8_t mask = 30;
    ipv4_print(ip, mask);

    int add_res = add(ip, mask);
    printf("is the ip a valid prefix: %s\n", add_res == -1 ? "no" : "yes");

    printf("192.0.24.0/24: %d\n", add(ipv4_from_octets(192,0,24,0), 24));
    printf("127.0.0.1/32: %d\n", add(ipv4_from_octets(127,0,0,1), 32));

    printf("###############BEFORE DELETE\n");
    _print_tree(NULL, 0, "head");

    (void)del(ipv4_from_octets(127,0,0,1), 32);
    (void)add(ipv4_from_octets(192 ,0 ,0 ,0), 16);

    printf("###############AFTER DELETE\n");
    _print_tree(NULL, 0, "head");

    printf("###############CHECK\n");
    uint8_t max_mask = check(ipv4_from_octets(192, 0, 24, 1));
    printf("Max mask: %d\n", max_mask);

    printf("End of test `%s`\n", __FILE__);
    return 0;
}