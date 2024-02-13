#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 16
#define BLOCK_SIZE 4

// Define a cache block structure
struct CacheBlock {
    int valid; // Valid bit
    int tag;   // Tag bits
    int data[BLOCK_SIZE];
};

// Initialize the cache
struct CacheBlock cache[CACHE_SIZE];

// Function to read data from memory
void readMemory(int address) {
    // Calculate block index, tag, and line index
    int block_index = address / BLOCK_SIZE;
    int tag = block_index / CACHE_SIZE;
    int line_index = block_index % CACHE_SIZE;

    // Check if the cache line is valid and has the same tag
    if (cache[line_index].valid && cache[line_index].tag == tag) {
        printf("Data read from cache at address %d:", address);
        for (int i = 0; i < BLOCK_SIZE; i++) {
            printf(" %d", cache[line_index].data[i]);
        }
        printf("\n");
    } else {
        // Cache miss, fetch data from memory
        printf("Cache miss. Fetching data from memory...\n");
        cache[line_index].valid = 1;
        cache[line_index].tag = tag;
        // Simulate fetching data from memory (replace this with actual memory access)
        for (int i = 0; i < BLOCK_SIZE; i++) {
            cache[line_index].data[i] = rand(); // Replace with actual memory access
        }
        printf("Data read from memory at address %d:", address);
        for (int i = 0; i < BLOCK_SIZE; i++) {
            printf(" %d", cache[line_index].data[i]);
        }
        printf("\n");
    }
}

int main() {
    int address;

    // Initialize cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].valid = 0;
        cache[i].tag = -1;
    }

    while (1) {
        printf("Enter a memory address to read (-1 to exit): ");
        scanf("%d", &address);

        if (address == -1) {
            break;
        }

        readMemory(address);
    }

    return 0;
}
