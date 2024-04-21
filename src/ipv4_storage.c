#include "ipv4_storage.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MASK_CIDR_TO_32BIT(_mask)      (~((1 << (32 - (_mask))) - 1))
#define GET_NTH_BIT(_number, _n)       (((_number) >> (_n)) & 0b1)

static ipv4_tree_node_t* _root = NULL;

int add(uint32_t base, int8_t mask) {
    // invalid mask - integer outside the range 0..32 (inclusive)
    if (mask < 0 || mask > 32)
        return -1;

    // invalid prefix - bits outside the mask are not all 0
    if (~MASK_CIDR_TO_32BIT(mask) & base)
        return -1;
    
    if (_root == NULL) {
        _root = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
        // malloc error - could not allocate the memory
        if (_root == NULL) 
            return -1;

        // initiailze to 0
        memset(_root, 0, sizeof(*_root));
    }

    ipv4_tree_node_t* current_node = _root;
    
    for (int i=0; i<mask; i++) {
        if (GET_NTH_BIT(base, 31-i)) {
            if (current_node->right == NULL) {
                current_node->right = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
                
                // malloc error - could not allocate the memory
                if (current_node->right == NULL) 
                    return -1;

                // initialization to 0
                memset(current_node->right, 0, sizeof(*current_node->right));
            }
            current_node = current_node->right;
        } else {
            if (current_node->left == NULL) {
                current_node->left = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
                
                // malloc error - could not allocate the memory
                if (current_node->left == NULL) 
                    return -1;

                // initialization to 0
                memset(current_node->left, 0, sizeof(*current_node->left));
            }
            current_node = current_node->left;
        }
    }

    current_node->occupied = true;
    return 0;
}

int del(uint32_t base, int8_t mask) {
    // invalid mask - integer outside the range 0..32 (inclusive)
    if (mask < 0 || mask > 32) {
        return -1;
    }

    // invalid prefix - bits outside the mask are not all 0
    if (~MASK_CIDR_TO_32BIT(mask) & base) {
        return -1;
    }

    // no root
    if (_root == NULL) {
        return 0;
    }

    ipv4_tree_node_t* current_node = _root;
    
    for (int i=0; i<mask; i++) {
        if (GET_NTH_BIT(base, 31-i)) {
            current_node = current_node->right;
        } else {            
            current_node = current_node->left;
        }

        // node is NULL - can't go deeper
        if (current_node == NULL) {
            return 0;
        }
    }

    if (current_node->occupied) {
        current_node->occupied = false;
    }

    return 0;
}

int8_t check(uint32_t ip) {
    ipv4_tree_node_t* current_node = _root;
    int8_t max_mask = -1;

    int8_t layer = 0;
    while (current_node != NULL) {
        if (current_node->occupied) {
            max_mask = layer;
        }

        if (GET_NTH_BIT(ip, 31-layer)) {
            current_node = current_node->right;
        } else {            
            current_node = current_node->left;
        }
        layer++;
    }

    return max_mask;
}

void ipv4_print(uint32_t address, int8_t mask) {
    printf("%d.%d.%d.%d/%d\n", 
        (address >> 24 & _BYTE_MASK),
        (address >> 16 & _BYTE_MASK),
        (address >> 8  & _BYTE_MASK),
        (address       & _BYTE_MASK),
        mask
    );
}

uint32_t ipv4_from_octets(int8_t a, int8_t b, int8_t c, int8_t d) {
    return (a << 24) + (b << 16) + (c << 8) + d;
}
