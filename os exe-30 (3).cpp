#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Inside the new thread\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, thread_function, NULL) != 0 ||
        pthread_create(&thread2, NULL, thread_function, NULL) != 0) {
        fprintf(stderr, "Error creating threads\n");
        return 1;
    }

    printf("Inside the main thread\n");

    if (pthread_equal(thread1, thread2)) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

