#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

struct Process {
    int process_id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void roundRobin(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int remaining_processes = n;

    int current_time = 0;
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > TIME_QUANTUM) {
                    current_time += TIME_QUANTUM;
                    processes[i].remaining_time -= TIME_QUANTUM;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].waiting_time = current_time - processes[i].burst_time;
                    if (processes[i].waiting_time < 0) {
                        processes[i].waiting_time = 0;
                    }
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                    processes[i].turnaround_time = current_time;
                }
            }
        }
    }

    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
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

    struct Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    roundRobin(processes, n);

    return 0;
}

