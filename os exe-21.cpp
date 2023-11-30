#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 1000
#define MAX_PROCESS 50

int memory[MEMORY_SIZE];
bool allocated[MAX_PROCESS];
int processSize[MAX_PROCESS];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        memory[i] = -1; // -1 indicates free memory
    }

    for (int i = 0; i < MAX_PROCESS; ++i) {
        allocated[i] = false;
        processSize[i] = 0;
    }
}

void worstFit(int size, int pid) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        int fragmentSize = 0;

        if (memory[i] == -1) {
            for (int j = i; j < MEMORY_SIZE && memory[j] == -1; ++j) {
                fragmentSize++;
            }

            if (fragmentSize >= size && fragmentSize > maxFragmentation) {
                maxFragmentation = fragmentSize;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        for (int i = worstFitIndex; i < worstFitIndex + size; ++i) {
            memory[i] = pid;
        }
        allocated[pid] = true;
        processSize[pid] = size;

        printf("Process %d allocated with worst fit.\n", pid);
    } else {
        printf("Process %d cannot be allocated with worst fit.\n", pid);
    }
}

void deallocate(int pid) {
    if (allocated[pid]) {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            if (memory[i] == pid) {
                memory[i] = -1;
            }
        }
        allocated[pid] = false;
        processSize[pid] = 0;

        printf("Process %d deallocated.\n", pid);
    } else {
        printf("Process %d not found or already deallocated.\n", pid);
    }
}

void displayMemory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

int main() {
    initializeMemory();

    // Allocate processes using worst fit
    worstFit(10,100);
    worstFit(20, 200);
    worstFit(30, 300);

    displayMemory();

    // Deallocate process
    deallocate(1);

    displayMemory();

    return 0;
}

