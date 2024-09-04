#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;
void writeFile(const char *filename) {
    FILE *file = fopen(filename, "w");  // Open the file in write mode

    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    char str[] = "Hello baby\n";

    // Write some text to the file
    fprintf(file, str);
 
    fclose(file);  // Close the file
}

 

void readFile(const char *filename, char *mode, int *quantumTime, int arrivalTime[], int burstTime[], int *numProcesses) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Reading the Mode
    fscanf(file, "Mode = %s\n", mode);

    // Reading the QuantumTime
    fscanf(file, "QuantumTime = %d\n", quantumTime);

    // Reading the ArrivalTime
    fscanf(file, "ArrivalTime =");
    *numProcesses = 0;
    while (fscanf(file, "%d", &arrivalTime[*numProcesses]) == 1) {
        (*numProcesses)++;
    }
    
    // Reading the BurstTime
    fscanf(file, "BurstTime =");
    for (int i = 0; i < *numProcesses; i++) {
        fscanf(file, "%d", &burstTime[i]);
    }

    fclose(file);
}


void writeInOutputFile(Process processes[], int n) {

    // Open a file for writing the output
    FILE *outputFile = fopen("OutputAns.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the output to the file
    fprintf(outputFile, "\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].pid, 
                processes[i].arrivalTime, 
                processes[i].burstTime, 
                processes[i].completionTime, 
                processes[i].turnaroundTime, 
                processes[i].waitingTime);
    }

    // Close the file
    fclose(outputFile);
}
 

int main() {
    // const char *filename = "myTest.txt";

     char mode[20];           // Store mode as a string
    int quantumTime;          // Store QuantumTime
    int arrivalTime[10];      // Array to store ArrivalTime
    int burstTime[10];        // Array to store BurstTime
    int numProcesses = 0;     // Number of processes (length of arrivalTime and burstTime arrays)

    readFile("myTest.txt", mode, &quantumTime, arrivalTime, burstTime, &numProcesses);

    // Print the values to verify
    printf("Mode: %s\n", mode);
    printf("QuantumTime: %d\n", quantumTime);
    printf("ArrivalTime: ");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d ", arrivalTime[i]);
    }
    printf("\nBurstTime: ");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d ", burstTime[i]);
    }
    printf("\n");


    return 0;
}
