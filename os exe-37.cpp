#include <stdio.h>
#include <stdlib.h>

#define TOTAL_REQUESTS 10 // Total number of disk requests

// Function to calculate the total head movement for FCFS
int calculateTotalHeadMovement(int requests[], int headPosition) {
    int totalHeadMovement = 0;
    for (int i = 0; i < TOTAL_REQUESTS; ++i) {
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

    int totalHeadMovement = calculateTotalHeadMovement(requests, initialHeadPosition);

    printf("Total Head Movement using FCFS: %d\n", totalHeadMovement);

    return 0;
}

