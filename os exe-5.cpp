#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int executed;
};

void priorityScheduling(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize waiting time and executed status
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = 0;
        processes[i].executed = 0;
    }

    // Find process with highest priority and execute
    int completed = 0, current_time = 0, highest_priority;
    while (completed != n) {
        highest_priority = -1;
        int min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].executed == 0 && processes[i].priority < min_priority && processes[i].burst_time > 0) {
                min_priority = processes[i].priority;
                highest_priority = i;
            }
        }

        if (highest_priority == -1) {
            current_time++;
            continue;
        }

        processes[highest_priority].burst_time--;
        current_time++;

        if (processes[highest_priority].burst_time == 0) {
            completed++;
            processes[highest_priority].turnaround_time = current_time;
            processes[highest_priority].executed = 1;
            processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - processes[highest_priority].burst_time;
            if (processes[highest_priority].waiting_time < 0) {
                processes[highest_priority].waiting_time = 0;
            }
        }
    }

    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].turnaround_time,
               processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }

    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2lf\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    priorityScheduling(processes, n);

    return 0;
}

