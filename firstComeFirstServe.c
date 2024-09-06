#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void findFirstComeFirstServe(Process processes[], int n)
{

    // Calculating completion time
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;

    for (int i = 1; i < n; i++)
    {
        if (processes[i].arrivalTime < processes[i - 1].completionTime)
        {
            processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
        }
        else
        {
            processes[i].completionTime = processes[i].arrivalTime + processes[i].burstTime;
        }
    }

    // Calculating turnaround time and waiting time
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

void displayProcessDetailsForFirstComeFirstServe(Process processes[], int n, char algoName[])
{

    // Open a file for writing the output
    char fileName[100];
    sprintf(fileName, "Test Cases/%s_output.txt", algoName); // Generate the file path

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

void readFileForFirstComeFirstServe(const char *filename, int *numProcesses, int arrivalTime[], int burstTime[])
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Reading the number of processes
    fscanf(file, "NoOfProcess = %d\n", numProcesses);

    // Reading the ArrivalTime
    fscanf(file, "ArrivalTime =");
    for (int i = 0; i < *numProcesses; i++)
    {
        fscanf(file, "%d", &arrivalTime[i]);
    }

    // Reading the BurstTime
    fscanf(file, "\nBurstTime =");
    for (int i = 0; i < *numProcesses; i++)
    {
        fscanf(file, "%d", &burstTime[i]);
    }

    fclose(file);
}


int firstComeFirstServe() {
    Process *processes;
    int NoOfProcess;
    int *arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
    int *burstTime = (int *)malloc(100 * sizeof(int));  

    readFileForFirstComeFirstServe("Test Cases/FirstComeFirstServe.txt", &NoOfProcess,arrivalTime,burstTime);

    processes = (Process *)malloc(NoOfProcess * sizeof(Process));

    for (int i = 0; i < NoOfProcess; i++) {
            processes[i].pid = i + 1;  // Assign a PID
            processes[i].arrivalTime = arrivalTime[i];
            processes[i].burstTime = burstTime[i];
    }


        findFirstComeFirstServe(processes, NoOfProcess);
        
        displayProcessDetailsForFirstComeFirstServe(processes, NoOfProcess, "FirstComeFirstServe");

    free(arrivalTime);
    free(burstTime);
     free(processes);

}