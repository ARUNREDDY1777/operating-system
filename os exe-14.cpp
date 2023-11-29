#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME 50

typedef struct {
    char filename[MAX_FILENAME];
    // Other file attributes can be added here
} FileEntry;

FileEntry files[MAX_FILES]; // Array to store file entries
int fileCount = 0; // Counter to track the number of files

void createFile(const char *filename) {
    if (fileCount >= MAX_FILES) {
        printf("Cannot create more files. Storage full.\n");
        return;
    }

    if (fileCount > 0) {
        // Check if the file already exists
        for (int i = 0; i < fileCount; i++) {
            if (strcmp(files[i].filename, filename) == 0) {
                printf("File '%s' already exists.\n", filename);
                return;
            }
        }
    }

    if (strlen(filename) > MAX_FILENAME) {
        printf("File name is too long.\n");
        return;
    }

    strcpy(files[fileCount].filename, filename);
    fileCount++;
    printf("File '%s' created successfully.\n", filename);
}

void displayFiles() {
    if (fileCount == 0) {
        printf("No files in the directory.\n");
        return;
    }

    printf("Files in the directory:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("- %s\n", files[i].filename);
    }
}

int main() {
    int choice;
    char filename[MAX_FILENAME];

    do {
        printf("\n1. Create a file\n");
        printf("2. Display files\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", filename);
                createFile(filename);
                break;
            case 2:
                displayFiles();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}


