#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 50 // Assuming each block size is 50 bytes
#define NUM_BLOCKS 10 // Total number of blocks in the file

// Structure defining a block of the file
typedef struct {
    char data[BLOCK_SIZE];
} Block;

// Function to write a block to a file
void writeBlock(FILE *file, const Block *block) {
    fwrite(block, sizeof(Block), 1, file);
}

// Function to read a block from a file at a given index
void readBlock(FILE *file, int blockIndex) {
    Block readBlock;
    fseek(file, blockIndex * sizeof(Block), SEEK_SET); // Move to the specified block index

    fread(&readBlock, sizeof(Block), 1, file);
    printf("Reading Block %d, Data: %s\n", blockIndex, readBlock.data);
}

int main() {
    FILE *file;
    Block blocks[NUM_BLOCKS]; // Example: Array of blocks representing the file

    // Initialize blocks with sample data
    for (int i = 0; i < NUM_BLOCKS; ++i) {
        snprintf(blocks[i].data, sizeof(blocks[i].data), "Block %d Data", i + 1);
    }

    // Write blocks to a file
    file = fopen("file_blocks.bin", "wb"); // Open file in binary write mode
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < NUM_BLOCKS; ++i) {
        writeBlock(file, &blocks[i]);
    }

    fclose(file);

    // Read blocks from the file based on block index (simulating the index block)
    file = fopen("file_blocks.bin", "rb"); // Open file in binary read mode
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Simulate accessing specific blocks using their index
    readBlock(file, 2); // Access block at index 2
    readBlock(file, 7); // Access block at index 7

    fclose(file);

    return 0;
}

