#include "ipv4_storage.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LOOP                            for(;;)
#define MASK_CIDR_TO_32BIT(_mask)      (~((1 << (32 - (_mask))) - 1))
#define GET_NTH_BIT(_number, _n)       (((_number) >> (_n)) & 0b1)

static ipv4_tree_node_t* _root = NULL;
static int add_counter = 0;
static int created_nodes = 0;
static int occupied_nodes = 0;

void _occupied_nodes(ipv4_tree_node_t* node, int layer) {
    if (node == NULL) return;
    if (node->occupied) occupied_nodes++;
    printf("layer: %d, node->left: 0x%p, node->right: 0x%p\n", layer, node->left, node->right);
    _occupied_nodes(node->left, layer+1);
    _occupied_nodes(node->right,layer+1);
}

int get_occupied_nodes(ipv4_tree_node_t* start) {
    occupied_nodes = 0;

    if (start == NULL) return 0;
    if (start->occupied) occupied_nodes++;
    _occupied_nodes(start->left, 1);
    _occupied_nodes(start->right, 1);

    return occupied_nodes;
}

// Function to print the binary tree in a user-friendly format
void printTree(ipv4_tree_node_t* root, int level) {
    if (root == NULL) return;

    // Print spaces proportional to the level for better visualization
    for (int i = 0; i < level; i++)
        printf(" ");

    // Print the data of the current node
    printf("%s\n", root->occupied ? "y" : "n");

    // Recursively print the left subtree
    printTree(root->left, level + 1);

    // Recursively print the right subtree
    printTree(root->right, level + 1);
}

void _print_tree(ipv4_tree_node_t* node, int count, const char* label) {
    if (node == NULL && strcmp(label, "head") == 0) {
        printf("Nodes: %d\n", add_counter);
        printf("Nodes created: %d = %lld B = %lld kB\n", 
            created_nodes, 
            created_nodes * sizeof(ipv4_tree_node_t), 
            created_nodes * sizeof(ipv4_tree_node_t) / 1024);
        printf("Occupied nodes: %d\n", get_occupied_nodes(_root));
        node = _root;
        printTree(_root, 0);
    }
    if (node == NULL) return;
    printf("layer %d, l/r: %s, occupied: %s\n", count, label, node->occupied ? "yes" : "no");
    _print_tree(node->left, count+1, "left");
    _print_tree(node->right, count+1, "right");
}

int add(uint32_t base, uint8_t mask) {
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
        _root->left = NULL;
        _root->right = NULL;
        _root->occupied = false;
        created_nodes++;
    }

    ipv4_tree_node_t* current_node = _root;
    int i=0;
    for (; i<mask; i++) {
        uint8_t current_bit = GET_NTH_BIT(base, 31-i);

        if (current_bit) {
            if (current_node->right == NULL) {
                current_node->right = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));
                
                // malloc error - could not allocate the memory
                if (current_node->right == NULL) {
                    perror("MALLOC RIGHT");
                    return -1;
                }
                current_node->right->occupied = false;
                current_node->right->left = NULL;
                current_node->right->right = NULL;
                created_nodes++;
            }

            current_node = current_node->right;
        } else {
            if (current_node->left == NULL) {
                current_node->left = (ipv4_tree_node_t*)malloc(sizeof(ipv4_tree_node_t));               

                // malloc error - could not allocate the memory
                if (current_node->left == NULL) 
                    return -1;

                current_node->left->occupied = false;
                current_node->left->left = NULL;
                current_node->left->right = NULL;
                created_nodes++;
            }

            current_node = current_node->left;
        }
    }

    current_node->occupied = true;
    add_counter++;
    return 0;
}

void ipv4_print(uint32_t address, uint8_t mask) {
    int i=0;

    LOOP {
        printf("%d", (address >> (8*(4-1-i))) & _BYTE_MASK);
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
