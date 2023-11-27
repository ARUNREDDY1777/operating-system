#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
    int turnaround_time;
};

void preemptivePriorityScheduling(struct Process processes[], int n) {
    int current_time = 0, completed = 0, highest_priority = 9999, shortest_remaining = 9999, idx = -1;
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed != n) {
        highest_priority = 9999;
        shortest_remaining = 9999;
        idx = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_remaining && processes[i].remaining_time > 0) {
                shortest_remaining = processes[i].remaining_time;
                highest_priority = processes[i].priority;
                idx = i;
            } else if (processes[i].arrival_time <= current_time && processes[i].remaining_time == shortest_remaining && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].remaining_time--;
            current_time++;

            if (processes[idx].remaining_time == 0) {
                completed++;
                int turnaround_time = current_time - processes[idx].arrival_time;
                processes[idx].remaining_time = shortest_remaining;
                processes[idx].arrival_time = current_time;
                total_waiting_time += turnaround_time - processes[idx].burst_time;
                total_turnaround_time += turnaround_time;
            }
        } else {
            current_time++;
        }
    }

    printf("Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,processes[i].burst_time, processes[i].priority, processes[i].burst_time,processes[i].turnaround_time);
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
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    preemptivePriorityScheduling(processes, n);

    return 0;
}

