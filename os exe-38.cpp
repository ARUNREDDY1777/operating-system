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

// Function to simulate SCAN disk scheduling algorithm
int simulateSCAN(int requests[], int headPosition) {
    sortRequests(requests);

    int totalHeadMovement = 0;
    int currentIndex = 0;
    int direction = 1; // 1 for moving right, -1 for moving left

    // Find the index where head position is located
    while (currentIndex < TOTAL_REQUESTS && requests[currentIndex] < headPosition) {
        currentIndex++;
    }

    // Simulate SCAN moving right
    for (int i = currentIndex; i < TOTAL_REQUESTS; ++i) {
        totalHeadMovement += abs(requests[i] - headPosition);
        headPosition = requests[i];
    }

    // If head is at the end, move back and service remaining requests
    totalHeadMovement += abs(DISK_SIZE - headPosition - 1);
    headPosition = DISK_SIZE - 1;

    for (int i = currentIndex - 1; i >= 0; --i) {
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

    int totalHeadMovement = simulateSCAN(requests, initialHeadPosition);

    printf("Total Head Movement using SCAN: %d\n", totalHeadMovement);

    return 0;
}

