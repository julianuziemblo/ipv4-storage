# IPv4 Storage
A simple C library for storing and managing a collection of IPv4 prefixes.

# Implementation
The IPv4 prefix collection is implemented using a simple binary tree. This data structure was chosen based on the ease of implementation and its minimal memory consumption (24 bytes/node). The add(), del() and check() functions are all $O(1)$ - they don't depend on the amount of IPv4 prefixes in the system and can make __at most__ 32 derefs. 

I chose not to deallocate any resources with the del() function - for further node adding. Instead, another function, free_unused(), is provided. It gives the end user more flexibility when it comes to memory management.

# Examples
All examples can be found in the `examples/src` directory. 

## Manual
A simple command line program that lets you test all of the library's functions manually.

## Small operations 
A simple program presenting some predefined operations on the collection.

## Bulk
Examples starting with _"bulk-"_. They are all about using the library's main three functions many times in a row.

## Building and running
`run.sh` is a simple shell script that lets you run any of the examples, like so:
```bash
./run.sh examples/src/manual_example.c
```

You can also of course build and run the example scripts on your own, with e.g. GCC, like so:
```bash
gcc -o manual_example examples/src/manual_example.c src/ipv4_storage.c -Wall
./manual_example
```

# Functions
- `add(base, mask)`: add an IPv4 prefix to the collection.
- `del(base, mask)`: delete an IPv4 prefix from the collection.
- `check(ip)`: check, if an IPv4 address is contained in the tree.
- `allocated_nodes()`: returns the number of allocated nodes in the tree.
- `size()`: returns the number of IPv4 prefixes in the tree.
- `free_unused()`: frees the memory of unused nodes in the tree.
- `ipv4_from_octets(a, b, c, d)`: creates an IPv4 address from 4 octets.
- `ipv4_prefix_print(address, mask)`: prints the provided IPv4 prefix to the stdout in the CIDR format.
- `ipv4_print(address)`: prints the provided IPv4 address to the stdout.

# Dependencies
- `gcc` - for the `run.sh` script
