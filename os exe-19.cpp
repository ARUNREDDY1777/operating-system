#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutexLock;
int sharedResource = 0;

void *threadFunction(void *arg) {
    int threadID = *((int *)arg);

    // Simulating critical section
    pthread_mutex_lock(&mutexLock); // Acquire the mutex lock

    printf("Thread %d is in critical section.\n", threadID);
    sharedResource++; // Accessing shared resource

    printf("Thread %d: Shared resource value after increment: %d\n", threadID, sharedResource);

    pthread_mutex_unlock(&mutexLock); // Release the mutex lock

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIDs[NUM_THREADS];

    pthread_mutex_init(&mutexLock, NULL); // Initialize the mutex lock

    for (int i = 0; i < NUM_THREADS; ++i) {
        threadIDs[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, &threadIDs[i])) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 1;
        }
    }

    pthread_mutex_destroy(&mutexLock); // Destroy the mutex lock

    return 0;
}

