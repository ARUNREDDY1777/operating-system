#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MAX_MSG_SIZE 100

// Define a structure for the message
struct message_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msg_queue_id;
    struct message_buffer message;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msg_queue_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue ID: %d\n", msg_queue_id);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process (sender)
        printf("Sender Process (PID: %d)\n", getpid());

        // Set up the message
        message.msg_type = 1;
        printf("Enter message to send: ");
        fgets(message.msg_text, MAX_MSG_SIZE, stdin);

        // Send the message
        if (msgsnd(msg_queue_id, (void *)&message, MAX_MSG_SIZE, 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Message sent: %s", message.msg_text);
    } else {
        // Child process (receiver)
        printf("Receiver Process (PID: %d)\n", getpid());

        // Receive the message
        if (msgrcv(msg_queue_id, (void *)&message, MAX_MSG_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Received Message: %s", message.msg_text);
    }

    // Remove the message queue (from the parent process)
    if (pid > 0 && msgctl(msg_queue_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

