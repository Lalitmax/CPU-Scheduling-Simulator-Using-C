#include <stdio.h>
#include <limits.h>

typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;


void findSJFWithPreemptive(Process proc[], int n) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = proc[i].burstTime;
    }

    int currentTime = 0;
    int complete = 0;
    int shortest = -1;
    int minBurst = INT_MAX;

    while (complete < n) {
        minBurst = INT_MAX;
        shortest = -1;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && remainingTime[i] < minBurst && remainingTime[i] > 0) {
                minBurst = remainingTime[i];
                shortest = i;
            }
        }

        // If no process is ready, increment time to the next arrival time
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Reduce remaining time of the selected process
        remainingTime[shortest]--;

        // If the process is finished, calculate its times
        if (remainingTime[shortest] == 0) {
            complete++;
            proc[shortest].completionTime = currentTime + 1;
            proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        }

        // Increment current time if a process is executed
        currentTime++;
    }
}

void findSJFWithNonPreemptive(Process proc[], int n) {
    int currentTime = 0;
    int complete = 0;
    int shortest = -1;

    while (complete < n) {
        int minBurst = INT_MAX;
        shortest = -1;

        // Find the process with the shortest burst time that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].completionTime == 0 && proc[i].burstTime < minBurst) {
                minBurst = proc[i].burstTime;
                shortest = i;
            }
        }

        // If no process is ready, increment time to the next arrival time
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // calc all CT, TAT, WT...
        currentTime += proc[shortest].burstTime;
        proc[shortest].completionTime = currentTime;
        proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;

        complete++;
    }
}