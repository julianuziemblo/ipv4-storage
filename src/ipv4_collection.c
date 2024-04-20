#include "ipv4_collection.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LOOP                            for(;;)
#define _MASK_CIDR_TO_32BIT(_mask)      (~((1 << (32 - (_mask))) - 1))
#define _GET_NTH_BIT(_number, _n)       (((_number) >> (_n)) & 0b1)

static ipv4_tree_node_t* _root = NULL;

void _print_tree(ipv4_tree_node_t* start, int count, const char* label) {
    if (start == NULL) return;
    printf("layer %d, l/r: %s, occupied: %s\n", count, label, start->occupied ? "yes" : "no");
    _print_tree(start->left, count+1, "left");
    _print_tree(start->right, count+1, "right");
}

int add(uint32_t base, uint8_t mask) {
    // invalid mask - integer outside the range 0..32 (inclusive)
    if (mask < 0 || mask > 32)
        return -1;

    // invalid prefix - bits outside the mask are not all 0
    if (~_MASK_CIDR_TO_32BIT(mask) & base)
        return -1;
    
    if (_root == NULL) {
        _root = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
        // malloc error - could not allocate the memory
        if (_root == NULL) 
            return -1;
    }

    ipv4_tree_node_t* current_node = _root;
    // printf("NULL is 0x%p\n", NULL);
    for (int i=0; i<mask; i++) {
        uint8_t current_bit = _GET_NTH_BIT(base, 31-i);
        //printf("[%d] Current bit: %d\n", i, current_bit);
        // printf("Current node is 0x%p\n", current_node);

        if (current_node == NULL) {
            printf("COS SIĘ MOCNO ZJEBALO!!!\n");
        }

        if (current_bit) {
            printf("Inside current_bit if, current_node is 0x%p\n", current_node);
            if (current_node->right == NULL) {
                printf("Current node.right is NULL. Adding value:\n");
                current_node->right = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
                
                // malloc error - could not allocate the memory
                if (current_node->right == NULL) 
                    return -1;
            }
            // printf("B4 assignment\n");
            current_node = current_node->right;
            // printf("Current node NOW is 0x%p\n", current_node);
        } else {
            if (current_node->left == NULL) {
                current_node->left = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
                // malloc error - could not allocate the memory
                if (current_node->left == NULL) 
                    return -1;
            }
            current_node = current_node->left;
        }
        // printf("Current node at the end of loop is 0x%p\n", current_node);
    }

    printf("current node at the end is: 0x%p\n", current_node);
    current_node->occupied = true;

    // _print_tree(_root, 0, "head");

    return 0;
}

void ipv4_print(uint32_t address, uint8_t mask) {
    int i=0;

    LOOP {
        printf("%d", (address >> (8*(4-1-i))) & _OCTET_MASK);
        i++;
        if (i>=4) {
            break;
        }
        printf(".");
    }
    
    printf("/%d\n", mask);
}

uint32_t ipv4_from_octets(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    return (a << 24) + (b << 16) + (c << 8) + d;
}

ipv4_tree_node_t* get_root() {
    return _root;
}
