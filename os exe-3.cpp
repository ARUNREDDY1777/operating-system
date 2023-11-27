#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

void calculateWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    waiting_time[0] = 0; // First process has 0 waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

void calculateAverageTime(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    calculateWaitingTime(processes, n, waiting_time);
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);

    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    int total_waiting_time = 0, total_turnaround_time = 0;

    // Display details for each process and calculate totals
    for (int i = 0; i < n; i++) {
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

    // Input details of each process
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        processes[i].arrival_time = 0; // All processes start at time 0
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    calculateAverageTime(processes, n);

    return 0;
}

