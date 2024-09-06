#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int isCompleted;
} Process;

void findSJFWithNonPreemptive( Process proc[], int n) {
    int complete = 0;
    int currentTime = 0;
    int shortest = -1;
    int minBurst = INT_MAX;

    while (complete < n) {
        minBurst = INT_MAX;
        shortest = -1;

        // Find the process with the shortest burst time that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].isCompleted == 0 && proc[i].burstTime < minBurst) {
                minBurst = proc[i].burstTime;
                shortest = i;
            }
        }

        // If no process is ready, increment time
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Execute the selected process completely
        currentTime += proc[shortest].burstTime;
        proc[shortest].completionTime = currentTime;
        proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        proc[shortest].isCompleted = 1;  // Mark the process as completed

        complete++;
    }
}


void findSJFWithPreemptive(Process proc[], int n) {
    int complete = 0;
    int currentTime = 0;
    int shortest = -1;
    int minRemaining = INT_MAX;  // To find the process with the shortest remaining time
    int finished = 0;            // To track when all processes are finished


    while (complete < n) {
        shortest = -1;
        minRemaining = INT_MAX;

        // Find the process with the shortest remaining time that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && proc[i].remainingTime < minRemaining) {
                minRemaining = proc[i].remainingTime;
                shortest = i;
            }
        }

        // If no process is ready, increment time and continue
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Decrease the remaining time of the selected process
        proc[shortest].remainingTime--;

        // If a process is completed
        if (proc[shortest].remainingTime == 0) {
            complete++;
            proc[shortest].completionTime = currentTime + 1;
            proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        }

        // Increment time for next iteration
        currentTime++;
    }
}

void displayProcessDetailsForShortestJobFirst(Process processes[], int n, char algoName[]) {
    // Open a file for writing the output
    char fileName[100];
    sprintf(fileName, "Test Cases/%s_output.txt", algoName);  // Generate the file path

    FILE *outputFile = fopen(fileName, "w");
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the table header with borders
    fprintf(outputFile, "+-----+--------------+------------+-----------------+-----------------+--------------+\n");
    fprintf(outputFile, "| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    fprintf(outputFile, "+-----+--------------+------------+-----------------+-----------------+--------------+\n");

    // Write each process's details in the table
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "| %3d | %12d | %10d | %15d | %15d | %12d |\n",
                processes[i].pid,
                processes[i].arrivalTime,
                processes[i].burstTime,
                processes[i].completionTime,
                processes[i].turnaroundTime,
                processes[i].waitingTime);
        fprintf(outputFile, "+-----+--------------+------------+-----------------+-----------------+--------------+\n");
    }

    // Close the file
    fclose(outputFile);
}

void readFileForShortestJobFirst(const char *filename, int *numProcesses, int arrivalTime[], int burstTime[], char mode[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "Mode = %s\n", mode);

    // Reading the number of processes
    fscanf(file, "NoOfProcess = %d\n", numProcesses);

    // Reading the ArrivalTime
    fscanf(file, "ArrivalTime =");
    for (int i = 0; i < *numProcesses; i++) {
        fscanf(file, "%d", &arrivalTime[i]);
    }

    // Reading the BurstTime
    fscanf(file, "\nBurstTime =");
    for (int i = 0; i < *numProcesses; i++) {
        fscanf(file, "%d", &burstTime[i]);
    }

    fclose(file);
}

void shortestJobFirst() {
    char mode[25]; 
    Process *processes;
    int NoOfProcess;
    int *arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
    int *burstTime = (int *)malloc(100 * sizeof(int));    // Adjust as needed

    readFileForShortestJobFirst("Test Cases/ShortestJobFirst.txt", &NoOfProcess, arrivalTime, burstTime, mode);

    processes = (Process*) malloc(NoOfProcess * sizeof(Process));

    // Initialize the process array
    for (int i = 0; i < NoOfProcess; i++) {
        processes[i].pid = i + 1;
        processes[i].arrivalTime = arrivalTime[i];
        processes[i].burstTime = burstTime[i];
        processes[i].remainingTime = burstTime[i];
        processes[i].isCompleted = 0;
    }

    if (strcmp(mode, "Preemptive") == 0) {
       
        
        findSJFWithPreemptive(processes, NoOfProcess);
        displayProcessDetailsForShortestJobFirst(processes, NoOfProcess, "ShortestJobFirstPreemptive");
    } else if(strcmp(mode, "NonPreemptive")==0){
        findSJFWithNonPreemptive(processes, NoOfProcess);
        displayProcessDetailsForShortestJobFirst(processes, NoOfProcess, "ShortestJobFirstNonPreemptive");
    }

    free(arrivalTime);
    free(burstTime);
    free(processes);
}
