#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 32
#define BLOCK_SIZE 4
#define L1_CACHE_SIZE 16
#define L1_LINES L1_CACHE_SIZE/BLOCK_SIZE

/*
Assumptions Made:1) the cache levels used in the code is only l1 cache..
                 2) the word being searched by the processor is either present in the l1 cache or in the main memory
                 3) no writing is happeing in the main memory for this code..only reading is happeing..
                 4) Random words are generated at every address in the main memory and it is displayed at the starting of the output
                 5) the user is the processor..the user is asked for input of the address that the processor needs...
                 6) size of the all the components are predifined..can be changed in the code itself
                 7) if user inputs the address that is greater than the size of the memory then an error message is displayed.. 
                 8) each word is of size 1 byte
*/

typedef struct CacheLine {
    int valid;
    int tag;
    int data[BLOCK_SIZE];
} CacheLine;

typedef struct Cache {
    int size;
    CacheLine* lines;
} Cache;

typedef struct MainMemory {
    int size;
    int data[MEMORY_SIZE];
} MainMemory;

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

MainMemory* initMainMemory() {
    MainMemory* memory = (MainMemory*)malloc(sizeof(MainMemory));
    memory->size = MEMORY_SIZE;
    srand(time(NULL));

    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory->data[i] = rand();
    }

    return memory;
}

int readFromCache(Cache* cache, int address) {
    int block_number = address / BLOCK_SIZE;
    int line_index = block_number % cache->size;

    if (cache->lines[line_index].valid && cache->lines[line_index].tag == block_number) {
        return cache->lines[line_index].data[address % BLOCK_SIZE];
    }

    // Cache miss
    return -1;
}

void writeToL1Cache(Cache* l1Cache, int address, int value, MainMemory* mainMemory) {
    int block_number = address / BLOCK_SIZE;
    int line_index = block_number % l1Cache->size;
    int offset = address % BLOCK_SIZE;

    if (!l1Cache->lines[line_index].valid || l1Cache->lines[line_index].tag != block_number) {
        printf("L1 Cache Miss - Fetching data from Main Memory...\n");

        l1Cache->lines[line_index].valid = 1;
        l1Cache->lines[line_index].tag = block_number;

        int block_start_address = block_number * BLOCK_SIZE;

        // Fetch one word at a time from Main Memory into the block
        for (int i = 0; i < BLOCK_SIZE; i++) {
            l1Cache->lines[line_index].data[i] = mainMemory->data[block_start_address + i];
            printf("Reading word %d from Main Memory to L1 Cache...\n", block_start_address+i);
            if (l1Cache->lines[line_index].data[i] == value) {
                printf("The required word is found..Passing the word to processor...\n(\"Continuing fetching the consequitive words to the cache if present..\")\n");
    }
        }
    }
    printf("\n");

    l1Cache->lines[line_index].data[offset] = value;

   
}

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

void displayMemoryContents(MainMemory* mainMemory) {
    printf("Main Memory Contents:\n\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d \n", mainMemory->data[i]);
        if ((i + 1) % BLOCK_SIZE == 0) {
            printf("\n");
        }
    }
}

int main() {
    Cache* l1Cache = initCache(L1_LINES);
    MainMemory* mainMemory = initMainMemory();

    displayMemoryContents(mainMemory);

    while (1) {
        int address;
        printf("Enter a memory address to read (-1 to exit): ");
        scanf("%d", &address);

        if (address == -1) {
            break;
        }

        int data = readFromCache(l1Cache, address);
        if (data == -1) {
            //printf("Data not found in L1 cache - Fetching from Main Memory...\n");
            data = mainMemory->data[address];
            writeToL1Cache(l1Cache, address, data, mainMemory);
        } else {
            printf("Data found in L1 cache - ");
            if (l1Cache->lines[address / BLOCK_SIZE % l1Cache->size].data[address % BLOCK_SIZE] == data) {
                printf("Passing the word to processor...\n");
            } else {
                printf("Cache contains the word, but it's different from what the processor requested.\n");
            }
        }

        displayCacheContents(l1Cache);
    }

    free(l1Cache->lines);
    free(l1Cache);
    free(mainMemory);

    return 0;
}
