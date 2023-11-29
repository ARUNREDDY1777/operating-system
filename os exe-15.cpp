#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 50
#define MAX_FILES_PER_DIR 50
#define MAX_FILENAME 50
#define MAX_DIRNAME 50

typedef struct {
    char filename[MAX_FILENAME];
    // Other file attributes can be added here
} FileEntry;

typedef struct {
    char dirname[MAX_DIRNAME];
    FileEntry files[MAX_FILES_PER_DIR];
    int fileCount;
    // Other directory attributes can be added here
} DirectoryEntry;

DirectoryEntry directories[MAX_DIRS]; // Array to store directory entries
int dirCount = 0; // Counter to track the number of directories

int findDirectory(const char *dirname) {
    for (int i = 0; i < dirCount; i++) {
        if (strcmp(directories[i].dirname, dirname) == 0) {
            return i; // Return index if directory exists
        }
    }
    return -1; // Directory not found
}

void createDirectory(const char *dirname) {
    if (dirCount >= MAX_DIRS) {
        printf("Cannot create more directories. Storage full.\n");
        return;
    }

    if (findDirectory(dirname) != -1) {
        printf("Directory '%s' already exists.\n", dirname);
        return;
    }

    if (strlen(dirname) > MAX_DIRNAME) {
        printf("Directory name is too long.\n");
        return;
    }

    strcpy(directories[dirCount].dirname, dirname);
    directories[dirCount].fileCount = 0;
    dirCount++;
    printf("Directory '%s' created successfully.\n", dirname);
}

void createFile(const char *dirname, const char *filename) {
    int dirIndex = findDirectory(dirname);

    if (dirIndex == -1) {
        printf("Directory '%s' does not exist.\n", dirname);
        return;
    }

    DirectoryEntry *dir = &directories[dirIndex];

    if (dir->fileCount >= MAX_FILES_PER_DIR) {
        printf("Cannot create more files in '%s'. Storage full.\n", dirname);
        return;
    }

    if (dir->fileCount > 0) {
        // Check if the file already exists in the directory
        for (int i = 0; i < dir->fileCount; i++) {
            if (strcmp(dir->files[i].filename, filename) == 0) {
                printf("File '%s' already exists in '%s'.\n", filename, dirname);
                return;
            }
        }
    }

    if (strlen(filename) > MAX_FILENAME) {
        printf("File name is too long.\n");
        return;
    }

    strcpy(dir->files[dir->fileCount].filename, filename);
    dir->fileCount++;
    printf("File '%s' created successfully in '%s'.\n", filename, dirname);
}

void displayFiles(const char *dirname) {
    int dirIndex = findDirectory(dirname);

    if (dirIndex == -1) {
        printf("Directory '%s' does not exist.\n", dirname);
        return;
    }

    DirectoryEntry *dir = &directories[dirIndex];

    if (dir->fileCount == 0) {
        printf("No files in '%s'.\n", dirname);
        return;
    }

    printf("Files in '%s':\n", dirname);
    for (int i = 0; i < dir->fileCount; i++) {
        printf("- %s\n", dir->files[i].filename);
    }
}

int main() {
    int choice;
    char dirname[MAX_DIRNAME];
    char filename[MAX_FILENAME];

    do {
        printf("\n1. Create a directory\n");
        printf("2. Create a file in a directory\n");
        printf("3. Display files in a directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                createDirectory(dirname);
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                printf("Enter file name: ");
                scanf("%s", filename);
                createFile(dirname, filename);
                break;
            case 3:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                displayFiles(dirname);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

