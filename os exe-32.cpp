#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

typedef struct {
    int pageNumber;
    int lastUsed;
    bool isValid;
} Page;

void lruPageReplacement(int pages[], int numPages) {
    Page frames[MAX_FRAMES];
    int pageFaults = 0;
    int time = 0;

    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i].isValid = false;
    }

    for (int i = 0; i < numPages; ++i) {
        bool pageExists = false;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j].isValid && frames[j].pageNumber == pages[i]) {
                pageExists = true;
                frames[j].lastUsed = time++;
                break;
            }
        }

        // Page fault, replace the least recently used page
        if (!pageExists) {
            printf("Page %d caused a page fault.\n", pages[i]);
            pageFaults++;

            int lruIndex = 0;
            for (int j = 1; j < MAX_FRAMES; ++j) {
                if (frames[j].isValid && frames[j].lastUsed < frames[lruIndex].lastUsed) {
                    lruIndex = j;
                }
            }

            if (frames[lruIndex].isValid) {
                printf("Replacing page %d with page %d.\n", frames[lruIndex].pageNumber, pages[i]);
            }

            frames[lruIndex].pageNumber = pages[i];
            frames[lruIndex].isValid = true;
            frames[lruIndex].lastUsed = time++;
        }

        // Display current state of frames
        printf("Current Frames: ");
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j].isValid) {
                printf("%d ", frames[j].pageNumber);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    lruPageReplacement(pages, numPages);

    return 0;
}

