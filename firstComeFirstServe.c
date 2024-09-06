#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process {
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;



void firstComeFirstServe(Process processes[], int n) {
 
    // Calculating completion time
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    
    for (int i = 1; i < n; i++) {
        if (processes[i].arrivalTime < processes[i - 1].completionTime) {
            processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
        } else {
            processes[i].completionTime = processes[i].arrivalTime + processes[i].burstTime;
        }
    }

    // Calculating turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

 }



