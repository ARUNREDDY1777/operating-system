#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS_COUNT 5 // Number of reader threads
#define WRITERS_COUNT 2 // Number of writer threads

sem_t mutex, writeBlock; // Semaphores for mutual exclusion and write lock
int data = 0; // Shared data

int readerCount = 0; // Counter to track the number of readers

void *reader(void *arg) {
    int readerID = *(int *)arg;

    while (1) {
        // Reader enters
        sem_wait(&mutex);
        readerCount++;

        if (readerCount == 1) {
            sem_wait(&writeBlock); // First reader locks write access
        }

        sem_post(&mutex);

        // Reading section
        printf("Reader %d reads data: %d\n", readerID, data);
        sleep(1); // Simulating reading time

        sem_wait(&mutex);
        readerCount--;

        if (readerCount == 0) {
            sem_post(&writeBlock); // Last reader unlocks write access
        }

        sem_post(&mutex);

        // Simulating time between successive reads
        sleep(2);
    }
}

void *writer(void *arg) {
    int writerID = *(int *)arg;

    while (1) {
        // Writing section
        sem_wait(&writeBlock);
        data++;
        printf("Writer %d writes data: %d\n", writerID, data);
        sem_post(&writeBlock);

        // Simulating time between successive writes
        sleep(3);
    }
}

int main() {
    pthread_t readerThreads[READERS_COUNT];
    pthread_t writerThreads[WRITERS_COUNT];

    int readerIDs[READERS_COUNT];
    int writerIDs[WRITERS_COUNT];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader threads
    for (int i = 0; i < READERS_COUNT; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readerThreads[i], NULL, reader, &readerIDs[i]);
    }

    // Create writer threads
    for (int i = 0; i < WRITERS_COUNT; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writerThreads[i], NULL, writer, &writerIDs[i]);
    }

    // Join threads
    for (int i = 0; i < READERS_COUNT; i++) {
        pthread_join(readerThreads[i], NULL);
    }

    for (int i = 0; i < WRITERS_COUNT; i++) {
        pthread_join(writerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

