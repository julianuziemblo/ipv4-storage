# IPv4 collection
A simple API with a tree-like structure for storing and managing a collection of IPv4 prefixes.

# Building and running
`run.sh` is a simple shell script that lets you run any of the examples, like so:
```bash
./run.sh examples/src/test.c
```

You can also of course build and run the example scripts on your own with e.g. GCC, like so:
```bash
gcc -o test1 examples/src/test1.c src/ipv4_storage.c -Wall
./test1
```

# Functions
- `add(uint32_t base, int8_t mask)`: add an IPv4 prefix to the collection.
- `del(uint32_t base, int8_t mask)`: delete an IPv4 prefix from the collection.
- `check(uint32_t ip)`: check, if an IPv4 address is contained in the tree.
- `ipv4_from_octets(int8_t a, int8_t b, int8_t c, int8_t d)`: creates an IPv4 address from 4 octets.
- `ipv4_print(uint32_t address, uint8_t mask)`: prints the provided IPv4 address to the stdout.