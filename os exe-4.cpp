#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time; // Remaining time for execution
};

void shortestRemainingTimeFirst(struct Process processes[], int n) {
    int complete = 0, time = 0, shortest = 0, min_remaining = 9999, finish_time;
    int waiting_time[n], turnaround_time[n];

    // Initialize remaining time of all processes
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && processes[j].remaining_time < min_remaining && processes[j].remaining_time > 0) {
                shortest = j;
                min_remaining = processes[j].remaining_time;
            }
        }

        processes[shortest].remaining_time--;

        min_remaining = processes[shortest].remaining_time;
        if (min_remaining == 0) {
            complete++;
            finish_time = time + 1;

            waiting_time[shortest] = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            if (waiting_time[shortest] < 0) {
                waiting_time[shortest] = 0;
            }
        }
        time++;
    }

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    int total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, waiting_time[i], turnaround_time[i]);
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

    shortestRemainingTimeFirst(processes, n);

    return 0;
}

