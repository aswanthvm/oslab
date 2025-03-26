#include <stdio.h>
#include <limits.h>

typedef struct {
    int process_id, arrival_time, burst_time, completion_time, turnaround_time, waiting_time, is_completed;
} Process;

void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void sjf_scheduling(Process processes[], int n) {
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    sort_by_arrival_time(processes, n);

    while (completed < n) {
        int min_burst_time = INT_MAX, next_process_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].burst_time < min_burst_time) {
                    min_burst_time = processes[i].burst_time;
                    next_process_index = i;
                }
            }
        }

        if (next_process_index == -1) {
            current_time++;
        } else {
            Process *p = &processes[next_process_index];
            p->completion_time = current_time + p->burst_time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            p->is_completed = 1;
            current_time = p->completion_time;
            total_waiting_time += p->waiting_time;
            total_turnaround_time += p->turnaround_time;
            completed++;
        }
    }

    printf("\n%-10s%-15s%-15s%-20s%-20s%-15s\n", "Process ID", "Arrival Time", "Burst Time", "Completion Time", "Turnaround Time", "Waiting Time");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-20d%-20d%-15d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter process details (Process ID, Arrival Time, Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].process_id, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].completion_time = 0;
        processes[i].is_completed = 0;
    }

    sjf_scheduling(processes, n);
    return 0;
}
