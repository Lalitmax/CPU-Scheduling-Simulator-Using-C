#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_scheduling_algo.h"

void displayProcessDetails(Process processes[], int n, char algoName[])
{
    // String comparison using strcmp
    if (strcmp(algoName, "FirstComeFirstServe") == 0 || strcmp(algoName, "ShortestJobFirst") == 0 || strcmp(algoName, "RoundRobin") == 0)
    {
        // Open a file for writing the output
        char fileName[100];
        sprintf(fileName, "Test Cases/%s_output.txt", algoName);  // Generate the file path

        FILE *outputFile = fopen(fileName, "w");
        if (outputFile == NULL)
        {
            printf("Error opening file!\n");
            return;
        }

        // Write the table header with borders
        fprintf(outputFile, "+-----+--------------+------------+-----------------+-----------------+--------------+\n");
        fprintf(outputFile, "| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
        fprintf(outputFile, "+-----+--------------+------------+-----------------+-----------------+--------------+\n");

        // Write each process's details in the table
        for (int i = 0; i < n; i++)
        {
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
    else if (strcmp(algoName, "PriorityScheduling") == 0)
    {
        // Open a file for writing the output
        char fileName[100];
        sprintf(fileName, "Test Cases/%s_output.txt", algoName);  // Generate the file path
        FILE *outputFile = fopen(fileName, "w");
        
        if (outputFile == NULL)
        {
            printf("Error opening file!\n");
            return;
        }

        // Write the table header with borders
        fprintf(outputFile, "+----------+-----+--------------+------------+-----------------+-----------------+--------------+\n");
        fprintf(outputFile, "| Priority | PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
        fprintf(outputFile, "+----------+-----+--------------+------------+-----------------+-----------------+--------------+\n");

        // Write each process's details in the table
        for (int i = 0; i < n; i++)
        {
            fprintf(outputFile, "| %5d  | %3d | %12d | %10d | %15d | %15d | %12d |\n",
                    processes[i].priority,
                    processes[i].pid,
                    processes[i].arrivalTime,
                    processes[i].burstTime,
                    processes[i].completionTime,
                    processes[i].turnaroundTime,
                    processes[i].waitingTime);
            fprintf(outputFile, "+----------+-----+--------------+------------+-----------------+-----------------+--------------+\n");
        }

        // Close the file
        fclose(outputFile);
    }
}

void readFile(const char *filename, char *mode, int *numProcesses, int arrivalTime[], int burstTime[], int *QuantumTime,  int priority[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Reading the Mode (algorithm name)
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

    // Reading the BurstTime
    fscanf(file, "\nPriority =");
    for (int i = 0; i < *numProcesses; i++) {
        fscanf(file, "%d", &priority[i]);
    }

    // Only read QuantumTime if the mode is "RoundRobin"
    // if (strcmp(mode, "RoundRobin") == 0) {
        fscanf(file, "\nQuantumTime = %d\n", QuantumTime);
    // }

    fclose(file);
}


int main() {
    Process *processes;
    char AlgorithmName[25];
    char mode[25];  // For storing scheduling mode
    int NoOfProcess;
    int QuantumTime;
    int *arrivalTime;
    int *burstTime;
    int *priority;

    FILE *algoName = fopen("Test Cases/AlgorithmName.txt", "r");

    if (algoName == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Reading the AlgorithmName
    fscanf(algoName, "AlgorithmName = %s\n", AlgorithmName);
    fclose(algoName);

    if (strcmp(AlgorithmName, "FirstComeFirstServe") == 0) {
        printf("FCFS");

        // Allocate memory for arrival and burst times
        arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
        burstTime = (int *)malloc(100 * sizeof(int));    // Adjust as needed
        priority   = (int *)malloc(100 * sizeof(int));  

        // Read the file
        readFile("Test Cases/FirstComeFirstServe.txt", mode, &NoOfProcess, arrivalTime, burstTime,&QuantumTime,priority);


        // Allocate memory for processes
        processes = (Process *)malloc(NoOfProcess * sizeof(Process));

        for (int i = 0; i < NoOfProcess; i++) {
            processes[i].pid = i + 1;  // Assign a PID
            processes[i].arrivalTime = arrivalTime[i];
            processes[i].burstTime = burstTime[i];
        }


        firstComeFirstServe(processes, NoOfProcess);
        
        displayProcessDetails(processes, NoOfProcess, AlgorithmName);


        // Free allocated memory
        free(arrivalTime);
        free(burstTime);
        free(processes);
    } else if (strcmp(AlgorithmName, "ShortestJobFirst") == 0) {
        printf("SJF");
        // Allocate memory for arrival and burst times
        arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
        burstTime = (int *)malloc(100 * sizeof(int));    // Adjust as needed
        priority   = (int *)malloc(100 * sizeof(int));  

        // Read the file
        readFile("Test Cases/ShortestJobFirst.txt", mode, &NoOfProcess, arrivalTime, burstTime,&QuantumTime,priority);


        // Allocate memory for processes
        processes = (Process *)malloc(NoOfProcess * sizeof(Process));
        printf("%d",NoOfProcess);
        
        for (int i = 0; i < NoOfProcess; i++) {
            processes[i].pid = i + 1;  // Assign a PID
            processes[i].arrivalTime = arrivalTime[i];
            processes[i].burstTime = burstTime[i];
        }

        if(strcmp(mode,"Preemptive")==0) {
            findSJFWithNonPreemptive(processes,NoOfProcess);
        }else {
            findSJFWithNonPreemptive(processes,NoOfProcess);

        }

        displayProcessDetails(processes, NoOfProcess, AlgorithmName);


        // Free allocated memory
        free(arrivalTime);
        free(burstTime);
        free(processes);

        // Similar logic for ShortestJobFirst
    } else if (strcmp(AlgorithmName, "RoundRobin") == 0) {
        printf("RoundRobin  ");
        // Allocate memory for arrival and burst times
        arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
        burstTime = (int *)malloc(100 * sizeof(int));    // Adjust as needed
        priority   = (int *)malloc(100 * sizeof(int));  

        // Read the file
        readFile("Test Cases/RoundRobin.txt", mode, &NoOfProcess, arrivalTime, burstTime,&QuantumTime,priority);


        // Allocate memory for processes
        processes = (Process *)malloc(NoOfProcess * sizeof(Process));
     
        
        for (int i = 0; i < NoOfProcess; i++) {
            processes[i].pid = i + 1;  // Assign a PID
            processes[i].arrivalTime = arrivalTime[i];
            processes[i].burstTime = burstTime[i];
        }

        // roundrobinTime(processes,NoOfProcess,QuantumTime);
        printf("%d",QuantumTime);
        displayProcessDetails(processes, NoOfProcess, AlgorithmName);


        // Free allocated memory
        free(arrivalTime);
        free(burstTime);
        free(processes);


        // Similar logic for RoundRobin
    } else if (strcmp(AlgorithmName, "PriorityScheduling") == 0) {
        // Similar logic for PriorityScheduling

        printf("PriorityScheduling  ");
        // Allocate memory for arrival and burst times
        arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
        burstTime = (int *)malloc(100 * sizeof(int)); 
        priority   = (int *)malloc(100 * sizeof(int));  
   

        // Read the file
        readFile("Test Cases/PriorityScheduling.txt", mode, &NoOfProcess, arrivalTime, burstTime,&QuantumTime,priority);


        // Allocate memory for processes
        processes = (Process *)malloc(NoOfProcess * sizeof(Process));
     
        
        for (int i = 0; i < NoOfProcess; i++) {
            processes[i].pid = i + 1;  // Assign a PID
            processes[i].arrivalTime = arrivalTime[i];
            processes[i].burstTime = burstTime[i];
            processes[i].priority = priority[i];
        }

        priorityScheduling(processes,NoOfProcess);
        displayProcessDetails(processes, NoOfProcess, AlgorithmName);


        // Free allocated memory
        free(arrivalTime);
        free(burstTime);
        free(processes);
    }

    return 0;
}
