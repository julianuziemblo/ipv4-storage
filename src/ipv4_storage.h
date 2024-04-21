#ifndef _IPV4_COLLECTION_H
#define _IPV4_COLLECTION_H 1

#define _BYTE_MASK 0b11111111

#include <stdbool.h>
#include <stdlib.h>

typedef unsigned int uint32_t;
typedef char int8_t;
typedef unsigned char uint8_t;

/// @brief A node in the IPv4 tree data structure.
typedef struct _ipv4_tree_node {
    struct _ipv4_tree_node* left;
    struct _ipv4_tree_node* right;
    bool occupied;
} ipv4_tree_node_t;

/// @brief Adds the provided IPv4 prefix to the tree.
/// @param base the IPv4 address prefix
/// @param mask the IPv4 address mask in CIDR notation
/// @return 0 on success or -1 when bad arguments are provided.
int add(uint32_t base, int8_t mask);

/// @brief Deletes the provided IPv4 prefix from the tree.
/// @param base the IPv4 address prefix
/// @param mask the IPv4 address mask in CIDR notation
/// @return 0 on success or -1 when bad arguments are provided.
int del(uint32_t base, int8_t mask);

/// @brief Checks, if an IPv4 address is contained in the prefix tree.
/// @param ip the IPv4 address to check
/// @return The biggest mask (of the most precise prefix) on match, -1 on no match.
int8_t check(uint32_t ip);

/// @brief The number of allocated nodes in the tree.
/// @return integer representing the number of allocated nodes in the tree.
size_t allocated_nodes();

/// @brief Size of the tree - number of IPv4 prefixes currently stored in the tree.
/// @return integer representing the number of IPv4 prefixes currently stored in the tree.
size_t size();

/// @brief Frees unused nodes in the IPv4 prefix tree.
void free_unused();

/// @brief Creates an IPv4 address from 4 octets.
/// @param a octet 1
/// @param b octet 2
/// @param c octet 3
/// @param d octet 4
/// @return A 32-bit unsigned integer representing the IPv4 address.
uint32_t ipv4_from_octets(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

/// @brief Prints the provided IPv4 prefix in the CIDR notation (`a.b.c.d/mask`) to the stdout.
/// @param address the IPv4 address to print
/// @param mask the IPv4 mask in CIDR notation
void ipv4_prefix_print(uint32_t address, int8_t mask);

/// @brief Prints the provided IPv4 address to the stdout.
/// @param address the IPv4 address to print
void ipv4_print(uint32_t address);

#endif