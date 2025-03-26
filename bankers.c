#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

bool isSafeState(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES]) {
    int work[MAX_RESOURCES];
    bool finish[processes];
    int safeSequence[processes];
    int count = 0;

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    while (count < processes) {
        bool found = false;

        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool canFinish = true;
                for (int r = 0; r < resources; r++) {
                    if (max[p][r] - allot[p][r] > work[r]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int r = 0; r < resources; r++) {
                        work[r] += allot[p][r];
                    }

                    finish[p] = true;
                    safeSequence[count++] = p;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int processes, resources;
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allot[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter available resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter max resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allot[i][j]);
        }
    }

    if (isSafeState(processes, resources, available, max, allot)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is in an unsafe state.\n");
    }

    return 0;
}
