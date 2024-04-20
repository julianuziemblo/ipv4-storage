#include "../src/ipv4_storage.h"
#include <stdio.h>

int main(void) {
    uint32_t ip = ipv4_from_octets(192,168,0,0);
    uint8_t mask = 9;
    ipv4_print(ip, mask);

    int add_res = add(ip, mask);
    printf("is the ip a valid prefix: %s\n", add_res == -1 ? "no" : "yes");

    (void)add(ipv4_from_octets(192 ,0 ,24 ,0), 24);
    (void)add(ipv4_from_octets(127,0,0,1), 32);

    printf("End of test `%s`\n", __FILE__);
    return 0;
}