#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

int numProcesses, numResources;

void initializeData() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the available resources: ");
    for (int i = 0; i < numResources; ++i) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources each process can claim:\n");
    for (int i = 0; i < numProcesses; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < numResources; ++j) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
        finished[i] = false;
    }

    printf("Enter the resources allocated to each process:\n");
    for (int i = 0; i < numProcesses; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < numResources; ++j) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }
}

bool checkSafety() {
    int work[MAX_RESOURCES];
    bool finish;

    for (int i = 0; i < numResources; ++i) {
        work[i] = available[i];
    }

    int order[numProcesses];
    int count = 0;

    while (count < numProcesses) {
        finish = false;

        for (int i = 0; i < numProcesses; ++i) {
            if (!finished[i]) {
                int j;
                for (j = 0; j < numResources; ++j) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == numResources) {
                    for (int k = 0; k < numResources; ++k) {
                        work[k] += allocation[i][k];
                    }
                    finished[i] = true;
                    order[count++] = i;
                    finish = true;
                }
            }
        }

        if (!finish) {
            break;
        }
    }

    if (count == numProcesses) {
        printf("System is in safe state.\nSafe sequence: ");
        for (int i = 0; i < numProcesses; ++i) {
            printf("%d ", order[i]);
        }
        printf("\n");
        return true;
    } else {
        printf("System is in unsafe state, deadlock might occur.\n");
        return false;
    }
}

int main() {
    initializeData();
    checkSafety();

    return 0;
}

