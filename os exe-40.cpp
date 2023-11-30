#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt";

    // Creating a file (if it doesn't exist)
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    fclose(file);

    // Set file permissions using chmod
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error changing file permissions");
        return 1;
    }

    // Display file permissions
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        perror("Error getting file status");
        return 1;
    }

    printf("File Permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return 0;
}

