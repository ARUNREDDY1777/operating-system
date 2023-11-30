
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 50 // Assuming each block size is 50 bytes

// Structure defining a block of the file
typedef struct Block {
    char data[BLOCK_SIZE];
    struct Block *next; // Pointer to the next block
} Block;

// Structure defining a file
typedef struct File {
    Block *firstBlock; // Pointer to the first block of the file
    Block *lastBlock;  // Pointer to the last block of the file
} File;

// Function to create a new block
Block *createBlock(const char *data) {
    Block *newBlock = (Block *)malloc(sizeof(Block));
    if (newBlock != NULL) {
        strncpy(newBlock->data, data, BLOCK_SIZE - 1);
        newBlock->data[BLOCK_SIZE - 1] = '\0';
        newBlock->next = NULL;
    }
    return newBlock;
}

// Function to add a block to the file
void addBlockToFile(File *file, const char *data) {
    Block *newBlock = createBlock(data);
    if (newBlock == NULL) {
        fprintf(stderr, "Error creating block\n");
        return;
    }

    if (file->firstBlock == NULL) {
        file->firstBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
    }
    file->lastBlock = newBlock;
}

// Function to display all blocks of a file
void displayFileBlocks(File *file) {
    Block *currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        printf("Block Data: %s\n", currentBlock->data);
        currentBlock = currentBlock->next;
    }
}

// Function to release memory occupied by blocks
void releaseFileMemory(File *file) {
    Block *currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        Block *temp = currentBlock;
        currentBlock = currentBlock->next;
        free(temp);
    }
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

int main() {
    File file;
    file.firstBlock = NULL;
    file.lastBlock = NULL;

    // Simulate adding blocks to the file
    addBlockToFile(&file, "Data for Block 1");
    addBlockToFile(&file, "Data for Block 2");
    addBlockToFile(&file, "Data for Block 3");

    // Display all blocks of the file
    displayFileBlocks(&file);

    // Release memory occupied by blocks
    releaseFileMemory(&file);

    return 0;
}

