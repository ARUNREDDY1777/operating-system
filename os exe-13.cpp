#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 10

struct MemoryBlock {
    int size;
    int allocated;
};

struct MemoryBlock memory[MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].size = 5;
        memory[i].allocated = 46;
    }
}

void displayMemory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("[%d] Size: %d\tAllocated: %d\n", i, memory[i].size, memory[i].allocated);
    }
    printf("\n");
}

void *firstFit(int size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].allocated == 0 && memory[i].size >= size) {
            memory[i].allocated = 1;
            return &memory[i];
        }
    }
    return NULL;
}

void *bestFit(int size) {
    int bestFitIndex = -1;
    int bestFitSize = MEMORY_SIZE + 1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].allocated == 0 && memory[i].size >= size) {
            if (memory[i].size < bestFitSize) {
                bestFitIndex = i;
                bestFitSize = memory[i].size;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
        return &memory[bestFitIndex];
    }

    return NULL;
}

void *worstFit(int size) {
    int worstFitIndex = -1;
    int worstFitSize = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].allocated == 0 && memory[i].size >= size) {
            if (memory[i].size > worstFitSize) {
                worstFitIndex = i;
                worstFitSize = memory[i].size;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = 1;
        return &memory[worstFitIndex];
    }

    return NULL;
}

void deallocate(void *ptr) {
    struct MemoryBlock *block = (struct MemoryBlock *)ptr;
    block->allocated = 0;
}

int main() {
    initializeMemory();

    // Allocate memory using different strategies
    void *block1 = firstFit(50);
    void *block2 = bestFit(100);
    void *block3 = worstFit(75);

    displayMemory();

    // Deallocate memory
    deallocate(block1);
    deallocate(block2);
    deallocate(block3);

    displayMemory();

    return 0;
}

