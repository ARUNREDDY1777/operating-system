#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Function to be executed by each thread
void *thread_function(void *thread_id) {
    int tid = *((int *)thread_id);
    printf("Thread %d: OPERSTING SYSTEM!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int rc, t;

    // Creating threads
    for (t = 0; t < NUM_THREADS; t++) {
        thread_args[t] = t;
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)&thread_args[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads have completed.\n");

    pthread_exit(NULL);
}

