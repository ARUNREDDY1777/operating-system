#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

void optimalPageReplacement(int pages[], int numPages) {
    int frames[MAX_FRAMES];
    bool isInFrame[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i] = -1; // Initialize frames with an invalid page number
        isInFrame[i] = false;
    }

    for (int i = 0; i < numPages; ++i) {
        bool pageExists = false;

        // Check if page already exists in frames
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j] == pages[i]) {
                pageExists = true;
                break;
            }
        }

        // Page fault, perform page replacement
        if (!pageExists) {
            printf("Page %d caused a page fault.\n", pages[i]);
            pageFaults++;

            int k;
            bool replaced = false;
            for (int j = 0; j < MAX_FRAMES; ++j) {
                if (!isInFrame[j]) {
                    frames[j] = pages[i];
                    isInFrame[j] = true;
                    replaced = true;
                    break;
                }
                int furthest = -1;
                for (k = i + 1; k < numPages; ++k) {
                    if (frames[j] == pages[k]) {
                        if (k > furthest) {
                            furthest = k;
                        }
                        break;
                    }
                }
                if (k == numPages) {
                    frames[j] = pages[i];
                    isInFrame[j] = true;
                    replaced = true;
                    break;
                }
            }
            if (!replaced) {
                for (int j = 0; j < MAX_FRAMES; ++j) {
                    if (frames[j] == pages[i]) {
                        for (int m = i + 1; m < numPages; ++m) {
                            if (frames[j] == pages[m]) {
                                if (m > k) {
                                    k = m;
                                }
                                break;
                            }
                        }
                    }
                }
                for (int j = 0; j < MAX_FRAMES; ++j) {
                    if (frames[j] == pages[i] && k == numPages) {
                        frames[j] = pages[i];
                        isInFrame[j] = true;
                        break;
                    }
                    if (frames[j] == pages[i] && k != numPages) {
                        frames[j] = pages[k];
                        isInFrame[j] = true;
                        break;
                    }
                }
            }

            // Display current state of frames
            printf("Current Frames: ");
            for (int j = 0; j < MAX_FRAMES; ++j) {
                if (isInFrame[j]) {
                    printf("%d ", frames[j]);
                } else {
                    printf("- ");
                }
            }
            printf("\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    optimalPageReplacement(pages, numPages);

    return 0;
}

