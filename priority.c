#include <stdio.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
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

int get_highest_priority_index(Process processes[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = 9999;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
            if (processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }
    }
    return highest_priority_index;
}

void priority_scheduling(Process processes[], int n) {
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    sort_by_arrival_time(processes, n);
    
    while (completed < n) {
        int index = get_highest_priority_index(processes, n, current_time);
        
        if (index == -1) {
            current_time++;
        } else {
            Process *p = &processes[index];
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

    printf("%-12s%-15s%-15s%-10s%-18s%-18s%-15s\n", "Process ID", "Arrival Time", "Burst Time", "Priority", "Completion Time", "Turnaround Time", "Waiting Time");
    for (int i = 0; i < n; i++) {
        printf("%-12d%-15d%-15d%-10d%-18d%-18d%-15d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        processes[i].process_id = i + 1;
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].is_completed = 0;
    }

    priority_scheduling(processes, n);

    return 0;
}

