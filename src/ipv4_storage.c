#include "ipv4_storage.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MASK_CIDR_TO_32BIT(_mask)      (~((1 << (32 - (_mask))) - 1))
#define GET_NTH_BIT(_number, _n)       (((_number) >> (_n)) & 0b1)

static ipv4_tree_node_t* _root = NULL;
static size_t _allocated_nodes = 0;
static size_t _size = 0;

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
        _allocated_nodes++;
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
                _allocated_nodes++;
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
                _allocated_nodes++;
            }
            current_node = current_node->left;
        }
    }

    if (!current_node->occupied) {
        _size++;
        current_node->occupied = true;
    }
    
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
        _size--;
    }

    return 0;
}

int8_t check(uint32_t ip) {
    ipv4_tree_node_t* current_node = _root;
    int8_t mask = -1;

    int8_t layer = 0;
    while (current_node != NULL) {
        if (current_node->occupied) {
            mask = layer;
        }

        if (GET_NTH_BIT(ip, 31-layer)) {
            current_node = current_node->right;
        } else {            
            current_node = current_node->left;
        }
        layer++;
    }

    return mask;
}

size_t allocated_nodes() {
    return _allocated_nodes;
}

size_t size() {
    return _size;
}

bool _free_unused_internal(ipv4_tree_node_t* node) {
    if (node == NULL) return true;
    if (node->occupied) return false;
    bool should_free_right = _free_unused_internal(node->right);
    if (should_free_right) node->right = NULL;

    bool should_free_left  = _free_unused_internal(node->left);
    if (should_free_left) node->left = NULL;

    if (should_free_right && should_free_left) {
        free(node);
        _allocated_nodes--;
        return true;
    }
    return false;
}

void free_unused() {
    (void)_free_unused_internal(_root);
}

void ipv4_prefix_print(uint32_t address, int8_t mask) {
    printf("%d.%d.%d.%d/%d\n", 
        (address >> 24 & _BYTE_MASK),
        (address >> 16 & _BYTE_MASK),
        (address >> 8  & _BYTE_MASK),
        (address       & _BYTE_MASK),
        mask
    );
}

void ipv4_print(uint32_t address) {
    printf("%d.%d.%d.%d\n", 
        (address >> 24 & _BYTE_MASK),
        (address >> 16 & _BYTE_MASK),
        (address >> 8  & _BYTE_MASK),
        (address       & _BYTE_MASK)
    );
}

uint32_t ipv4_from_octets(uint8_t a, uint8_t  b, uint8_t  c, uint8_t  d) {
    return (a << 24) + (b << 16) + (c << 8) + d;
}
