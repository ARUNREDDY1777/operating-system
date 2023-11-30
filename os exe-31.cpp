#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

typedef struct {
    int pageNumber;
    bool isValid;
} Page;

void fifoPageReplacement(int pages[], int numPages) {
    Page frames[MAX_FRAMES];
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i].isValid = false;
    }

    for (int i = 0; i < numPages; ++i) {
        bool pageExists = false;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j].isValid && frames[j].pageNumber == pages[i]) {
                pageExists = true;
                break;
            }
        }

        // Page fault, replace the oldest page
        if (!pageExists) {
            printf("Page %d caused a page fault.\n", pages[i]);
            pageFaults++;

            if (frames[frameIndex].isValid) {
                printf("Replacing page %d with page %d.\n", frames[frameIndex].pageNumber, pages[i]);
            }

            frames[frameIndex].pageNumber = pages[i];
            frames[frameIndex].isValid = true;
            frameIndex = (frameIndex + 1) % MAX_FRAMES;
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
    int pages[MAX_PAGES] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    fifoPageReplacement(pages, numPages);

    return 0;
}

