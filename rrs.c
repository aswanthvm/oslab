#include <stdio.h>

typedef struct {
    int processid, arrival, burst, temp_burst, completion, waiting, turnaround;
} Process;

int main() {
    int n, TQ;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival and burst time for P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].temp_burst = processes[i].burst;
        processes[i].processid = i;
    }
    
    printf("Enter Time Quantum: ");
    scanf("%d", &TQ);
    
    int queue[100], front = 0, rear = 0, current_time = 0, completed = 0;
    float avgwt = 0, avgtat = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && processes[i].temp_burst > 0) {
                queue[rear++] = i;
            }
        }
        
        if (front == rear) {
            current_time++;
            continue;
        }
        
        int p = queue[front++];
        printf("Executing P%d at time %d\n", p + 1, current_time);
        
        if (processes[p].temp_burst > TQ) {
            processes[p].temp_burst -= TQ;
            current_time += TQ;
            queue[rear++] = p;
        } else {
            current_time += processes[p].temp_burst;
            processes[p].temp_burst = 0;
            processes[p].completion = current_time;
            processes[p].turnaround = processes[p].completion - processes[p].arrival;
            processes[p].waiting = processes[p].turnaround - processes[p].burst;
            completed++;
        }
    }
    
    printf("\nProcess Arrival Burst Completion Turnaround Waiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%-7d%-8d%-6d%-11d%-11d%-7d\n", i + 1, processes[i].arrival, processes[i].burst, processes[i].completion,
               processes[i].turnaround, processes[i].waiting);
        avgwt += processes[i].waiting;
        avgtat += processes[i].turnaround;
    }
    
    printf("\nAverage Waiting Time = %.2f\n", avgwt / n);
    printf("Average Turnaround Time = %.2f\n", avgtat / n);
    
    return 0;
}
