#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 2// Size of the buffer

sem_t empty, full, mutex; // Semaphores

int buffer[BUFFER_SIZE]; // Buffer for the shared data
int count = 1; // Variable to keep track of the item count in the buffer

void *producer(void *arg) {
    int item = 0;

    while (1) {
        sleep(1); // Simulating production time
        item++; // Produce an item
        item<=10;
        sem_wait(&empty);
        sem_wait(&mutex);

        // Add item to the buffer
        buffer[count] = item;
        printf("Produced item: %d\n", item);
        count++;

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int item;

    while (1) {
        sleep(1); // Simulating consumption time

        sem_wait(&full);
        sem_wait(&mutex);

        // Consume item from the buffer
        item = buffer[count - 1];
        printf("Consumed item: %d\n", item);
        count--;

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

