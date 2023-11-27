#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int executed;
};

void nonPreemptiveSJF(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize executed status for all processes
    for (int i = 0; i < n; i++) {
        processes[i].executed = 0;
    }

    int completed = 0, current_time = 0, shortest, shortest_burst = 9999;

    while (completed != n) {
        shortest = -1;
        shortest_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].executed == 0 && processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest = i;
            }
        }

        if (shortest != -1) {
            current_time += processes[shortest].burst_time;
            processes[shortest].turnaround_time = current_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            if (processes[shortest].waiting_time < 0) {
                processes[shortest].waiting_time = 0;
            }
            processes[shortest].executed = 1;
            completed++;
        } else {
            current_time++;
        }
    }

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
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
    }

    nonPreemptiveSJF(processes, n);

    return 0;
}

