#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 3
#define EATING_TIME 2
#define THINKING_TIME 1

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher_action(void *arg) {
    int philosopher_id = *((int *)arg);
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", philosopher_id);
        sleep(THINKING_TIME);

        // Start eating (attempt to acquire forks)
        printf("Philosopher %d is hungry...\n", philosopher_id);
        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d picked up left fork %d\n", philosopher_id, left_fork);
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up right fork %d\n", philosopher_id, right_fork);

        // Eating
        printf("Philosopher %d is eating...\n", philosopher_id);
        sleep(EATING_TIME);

        // Done eating (release forks)
        pthread_mutex_unlock(&forks[left_fork]);
        printf("Philosopher %d put down left fork %d\n", philosopher_id, left_fork);
        pthread_mutex_unlock(&forks[right_fork]);
        printf("Philosopher %d put down right fork %d\n", philosopher_id, right_fork);
    }
}

int main() {
    int i, id[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each fork
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher_action, &id[i]);
    }

    // Join threads (will not reach this point in this example)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

