#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants for cache and memory sizes
#define MEMORY_SIZE 16 // Total memory size (words)
#define BLOCK_SIZE 4   // Words per block
#define L1_CACHE_SIZE 4
#define L2_CACHE_SIZE 8

// Data structure to represent a cache line
typedef struct CacheLine {
    int valid;
    int tag;
    int data[BLOCK_SIZE];
} CacheLine;

// Data structure to represent a cache
typedef struct Cache {
    int size;
    CacheLine* lines;
} Cache;

// Data structure to represent main memory
typedef struct MainMemory {
    int size;
    int data[MEMORY_SIZE];
} MainMemory;

// Initialize a cache with a given size
Cache* initCache(int size) {
    Cache* cache = (Cache*)malloc(sizeof(Cache));
    cache->size = size;
    cache->lines = (CacheLine*)malloc(size * sizeof(CacheLine));

    for (int i = 0; i < size; i++) {
        cache->lines[i].valid = 0;
        cache->lines[i].tag = -1;
    }

    return cache;
}

// Initialize main memory with random data
MainMemory* initMainMemory() {
    MainMemory* memory = (MainMemory*)malloc(sizeof(MainMemory));
    memory->size = MEMORY_SIZE;
    srand(time(NULL));

    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory->data[i] = rand(); // Random data between 0 and 255
    }

    return memory;
}

// Read data from cache
int readFromCache(Cache* cache, int address) {
    int block_number = address / BLOCK_SIZE;
    int line_index = block_number % cache->size;

    if (cache->lines[line_index].valid && cache->lines[line_index].tag == block_number) {
        return cache->lines[line_index].data[address % BLOCK_SIZE];
    }

    return -1; // Cache miss
}

// Write data to cache
void writeToCache(Cache* cache, int address, int value, MainMemory* mainMemory) {
    int block_number = address / BLOCK_SIZE;
    int line_index = block_number % cache->size;

    if (!cache->lines[line_index].valid || cache->lines[line_index].tag != block_number) {
        // Cache miss or a different block, fetch the entire block
        cache->lines[line_index].valid = 1;
        cache->lines[line_index].tag = block_number;

        int block_start_address = block_number * BLOCK_SIZE;
        for (int i = 0; i < BLOCK_SIZE; i++) {
            cache->lines[line_index].data[i] = mainMemory->data[block_start_address + i];
        }
    }

    // Update the specific word in the cache line
    cache->lines[line_index].data[address % BLOCK_SIZE] = value;
}

// Display the contents of a cache
void displayCacheContents(Cache* cache) {
    printf("Cache Contents:\n");
    for (int i = 0; i < cache->size; i++) {
        if (cache->lines[i].valid) {
            printf("Line %d (Tag: %d): ", i, cache->lines[i].tag);
            for (int j = 0; j < BLOCK_SIZE; j++) {
                printf("%d ", cache->lines[i].data[j]);
            }
            printf("\n");
        } else {
            printf("Line %d is empty\n", i);
        }
    }
    printf("\n");
}

int main() {
    Cache* l1Cache = initCache(L1_CACHE_SIZE);
    Cache* l2Cache = initCache(L2_CACHE_SIZE);

    MainMemory* mainMemory = initMainMemory(); // Declare and initialize mainMemory here

    while (1) {
        int address;
        printf("Enter a memory address to read (-1 to exit): ");
        scanf("%d", &address);

        if (address == -1) {
            break;
        }

        int data = readFromCache(l1Cache, address);

        if (data == -1) {
            // Cache miss in L1, check L2
            data = readFromCache(l2Cache, address);

            if (data == -1) {
                // Cache miss in L2, fetch from main memory
                data = mainMemory->data[address];
                writeToCache(l2Cache, address, data, mainMemory);

                printf("Getting data from Memory (Address %d): %d\n", address, data);
            } else {
                printf("Getting data from Level 2 Cache (Address %d): %d\n", address, data);
            }

            writeToCache(l1Cache, address, data, mainMemory);
        }

        printf("Data read from memory at address %d: %d\n", address, data);

        // Display cache contents
        displayCacheContents(l1Cache);
        displayCacheContents(l2Cache);
    }

    free(l1Cache->lines);
    free(l1Cache);
    free(l2Cache->lines);
    free(l2Cache);
    free(mainMemory);

    return 0;
}
