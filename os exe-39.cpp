#include <stdio.h>
#include <stdlib.h>

#define TOTAL_REQUESTS 10 // Total number of disk requests
#define DISK_SIZE 200     // Total size of the disk

// Function to sort requests in ascending order
void sortRequests(int requests[]) {
    for (int i = 0; i < TOTAL_REQUESTS - 1; ++i) {
        for (int j = 0; j < TOTAL_REQUESTS - i - 1; ++j) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to simulate C-SCAN disk scheduling algorithm
int simulateCSCAN(int requests[], int headPosition) {
    sortRequests(requests);

    int totalHeadMovement = 0;
    int currentIndex = 0;

    // Find the index where head position is located
    while (currentIndex < TOTAL_REQUESTS && requests[currentIndex] < headPosition) {
        currentIndex++;
    }

    // Simulate C-SCAN moving right
    for (int i = currentIndex; i < TOTAL_REQUESTS; ++i) {
        totalHeadMovement += abs(requests[i] - headPosition);
        headPosition = requests[i];
    }

    // Simulate the jump to the beginning of the disk
    totalHeadMovement += abs(DISK_SIZE - 1 - headPosition);
    headPosition = 0;

    // Service remaining requests at the beginning of the disk
    for (int i = 0; i < currentIndex; ++i) {
        totalHeadMovement += abs(requests[i] - headPosition);
        headPosition = requests[i];
    }

    return totalHeadMovement;
}

int main() {
    int requests[TOTAL_REQUESTS] = {98, 183, 37, 122, 14, 124, 65, 67, 38, 100};
    int initialHeadPosition = 53; // Initial head position

    printf("Disk Requests: ");
    for (int i = 0; i < TOTAL_REQUESTS; ++i) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    int totalHeadMovement = simulateCSCAN(requests, initialHeadPosition);

    printf("Total Head Movement using C-SCAN: %d\n", totalHeadMovement);

    return 0;
}

