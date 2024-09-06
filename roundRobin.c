#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;
int N = 0;

// Check if the queue is empty
bool isEmpty2() {
    return N == 0;
}

// Push a process index to the queue
void push(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty2()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    N++;
}

// Pop a process index from the queue
int pop() {
    if (isEmpty2()) return INT_MAX;  // Error case
    Node *temp = head;
    head = head->next;
    int currData = temp->data;
    N--;
    free(temp);
    return currData;
}

typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void displayProcessDetailsForRoundRobin(Process processes[], int n, char algoName[]) {
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

void readFileForRoundRobin(const char *filename, int *numProcesses, int arrivalTime[], int burstTime[], int *QuantumTime) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

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

    // Reading the QuantumTime
    fscanf(file, "\nQuantumTime = %d\n", QuantumTime);

    fclose(file);
}

void roundrobinTime() {
    Process *processes;
    int NoOfProcess;
    int QuantumTime;
    int *arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
    int *burstTime = (int *)malloc(100 * sizeof(int));    // Adjust as needed
    
    readFileForRoundRobin("Test Cases/RoundRobin.txt", &NoOfProcess, arrivalTime, burstTime, &QuantumTime);

    processes = (Process*) malloc(NoOfProcess * sizeof(Process));

    // Initialize the process array
    for (int i = 0; i < NoOfProcess; i++) {
        processes[i].pid = i + 1;
        processes[i].arrivalTime = arrivalTime[i];
        processes[i].burstTime = burstTime[i];
    }

    int remainingBurstTime[NoOfProcess];

    // Initialize remaining burst times
    for (int i = 0; i < NoOfProcess; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    push(0);  // Push the first process
    int currTime = processes[0].arrivalTime;  // Start at the first process arrival time
    int i = 1;  // Start tracking the second process

    while (!isEmpty2()) {
        int currProcessidx = pop();

        // Process execution
        if (remainingBurstTime[currProcessidx] >= QuantumTime) {
            remainingBurstTime[currProcessidx] -= QuantumTime;
            currTime += QuantumTime;
        } else {
            currTime += remainingBurstTime[currProcessidx];
            remainingBurstTime[currProcessidx] = 0;
        }

        // Check if new processes have arrived while the current one was executing
        while (i < NoOfProcess && processes[i].arrivalTime <= currTime) {
            push(i);
            i++;
        }

        // Re-add the current process if it hasn't finished
        if (remainingBurstTime[currProcessidx] > 0) {
            push(currProcessidx);
        } else {
            // Process is finished, set completion time
            processes[currProcessidx].completionTime = currTime;
        }

        // If the queue is empty but there are still processes that haven't arrived,
        // move the current time to the arrival time of the next process
        if (isEmpty2() && i < NoOfProcess) {
            currTime = processes[i].arrivalTime;
            push(i);
            i++;
        }
    }

    // Calculate turnaround time and waiting time for each process
    for (int i = 0; i < NoOfProcess; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

    // Display process details in an output file
    displayProcessDetailsForRoundRobin(processes, NoOfProcess, "RoundRobin");

    // Free dynamically allocated memory
    free(processes);
    free(arrivalTime);
    free(burstTime);
}

 