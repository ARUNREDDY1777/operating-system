#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define DATA_SIZE 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t full, empty;

void *producer(void *arg) {
    int *data = (int *)arg;
    for (int i = 0; i < DATA_SIZE; ++i) {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }
        buffer[in] = data[i];
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produced: %d\n", data[i]);

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int *result = (int *)malloc(DATA_SIZE * sizeof(int));
    for (int i = 0; i < DATA_SIZE; ++i) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }
        result[i] = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumed: %d\n", result[i]);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(result);
}

int main() {
    pthread_t prodThread, consThread;
    int producerData[DATA_SIZE];

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    // Generating data for producers
    for (int i = 0; i < DATA_SIZE; ++i) {
        producerData[i] = i + 1;
    }

    // Create producer and consumer threads
    pthread_create(&prodThread, NULL, producer, (void *)producerData);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prodThread, NULL);
    int *consumedData;
    pthread_join(consThread, (void **)&consumedData);

    // Free allocated memory for consumer result
    free(consumedData);

    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}

