#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define L1_SIZE 4       // Number of lines in L1 cache
#define L2_SIZE 16      // Number of lines in L2 cache
#define BLOCK_SIZE 4    // Number of words per block
#define WORD_SIZE 1     // Size of each word in bytes
#define MEMORY_SIZE (32 * BLOCK_SIZE * WORD_SIZE)

// Cache Line Structure
typedef struct {
    int valid;
    int tag;
    char data[BLOCK_SIZE * WORD_SIZE];
} CacheLine;

// L1 and L2 Cache Arrays
CacheLine l1_cache[L1_SIZE];
CacheLine l2_cache[L2_SIZE];

// Memory Array
char memory[MEMORY_SIZE];

// Function to Initialize Memory with Unique Data Blocks
void initializeMemory() {
    srand(time(NULL));
    srand(time(NULL));
    for (int i = 0; i < 32*BLOCK_SIZE * WORD_SIZE; i++) {
        memory[i] = rand() % 256; // Random data between 0 and 255
    }
    }


// Function to Read Data from Memory
void readMemory(int address, char* data) {
    // Calculate cache indices, tags, and offsets based on the address
    int l1_index = (address / BLOCK_SIZE) % L1_SIZE;
    int l1_tag = address / (L1_SIZE * BLOCK_SIZE);
    int l2_index = (address / BLOCK_SIZE) % L2_SIZE;
    int l2_tag = address / (L2_SIZE * BLOCK_SIZE);
    int offset = address % BLOCK_SIZE;

    // Check L1 cache
    if (l1_cache[l1_index].valid && l1_cache[l1_index].tag == l1_tag) {
        // Data is in L1 cache
        for (int i = 0; i < BLOCK_SIZE; i++) {
            data[i] = l1_cache[l1_index].data[i];
        }
    } else {
        // Data is not in L1 cache, check L2 cache
        if (l2_cache[l2_index].valid && l2_cache[l2_index].tag == l2_tag) {
            // Data is in L2 cache, copy to L1 cache (CWF policy)
            for (int i = 0; i < BLOCK_SIZE; i++) {
                l1_cache[l1_index].data[i] = l2_cache[l2_index].data[i];
            }
            l1_cache[l1_index].valid = 1;
            l1_cache[l1_index].tag = l1_tag;

            // Return the critical word to the processor
            data[0] = l1_cache[l1_index].data[offset];

            // Bring the remaining data into the L1 cache
            for (int i = 1; i < BLOCK_SIZE; i++) {
                data[i] = l1_cache[l1_index].data[i];
            }
        } else {
            // Data is not in L1 or L2 cache, fetch from memory
            int memoryBlockStart = address - offset;
            for (int i = 0; i < BLOCK_SIZE; i++) {
                l1_cache[l1_index].data[i] = memory[memoryBlockStart + i];
            }
            l1_cache[l1_index].valid = 1;
            l1_cache[l1_index].tag = l1_tag;

            // Copy data to L2 cache
            for (int i = 0; i < BLOCK_SIZE; i++) {
                l2_cache[l2_index].data[i] = l1_cache[l1_index].data[i];
            }
            l2_cache[l2_index].valid = 1;
            l2_cache[l2_index].tag = l2_tag;

            // Return the critical word to the processor
            data[0] = l1_cache[l1_index].data[offset];

            // Bring the remaining data into the L1 cache
            for (int i = 1; i < BLOCK_SIZE; i++) {
                data[i] = l1_cache[l1_index].data[i];
            }
        }
    }
}


// Function to Print Cache Contents
void printCache(CacheLine cache[], int size) {
    printf("Cache Contents:\n");
    for (int i = 0; i < size; i++) {
        if (cache[i].valid) {
            printf("Line %d (Tag: %d): ", i, cache[i].tag);
            for (int j = 0; j < BLOCK_SIZE * WORD_SIZE; j++) {
                printf("%d ", cache[i].data[j]);
            }
            printf("\n");
        } else {
            printf("Line %d is empty\n", i);
        }
    }
}

int main() {
    initializeMemory();

    while (1) {
        int address;
        printf("Enter a memory address to read (-1 to exit): ");
        scanf("%d", &address);

        if (address == -1) {
            break;
        }

        char data[BLOCK_SIZE * WORD_SIZE];
        readMemory(address, data);

        printf("Data read from memory at address %d: ", address);
        for (int i = 0; i < BLOCK_SIZE * WORD_SIZE; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");

        // Print Cache Contents
        printCache(l1_cache, L1_SIZE);
        printCache(l2_cache, L2_SIZE);
    }

    return 0;
}
