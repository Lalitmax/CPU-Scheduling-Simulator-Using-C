#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Process {
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;



typedef struct {
    int index;
    int priority;
} Pair;

typedef struct {
    Pair *arr;
    int size;
} MaxHeap;

MaxHeap* createHeap() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->arr = NULL;
    heap->size = 0;
    return heap;
}

void swap(Pair *x, Pair *y) {
    Pair temp = *x;
    *x = *y;
    *y = temp;
}

void add(MaxHeap* heap, int index, int priority) {
    // Increase heap size
    heap->size += 1;
    heap->arr = realloc(heap->arr, heap->size * sizeof(Pair));

    // Add the new element at the end
    int i = heap->size - 1;
    heap->arr[i].index = index;
    heap->arr[i].priority = priority;

    // Heapify: Adjust the position of the new element
    int parent = (i - 1) / 2;
    while (i > 0 && heap->arr[i].priority > heap->arr[parent].priority) {
        swap(&heap->arr[i], &heap->arr[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

Pair peek(MaxHeap* heap) {
    if (heap->size > 0) {
        return heap->arr[0];
    }
    return (Pair){-1, -1}; // or some error code
}

void heapify(MaxHeap* heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int maxIdx = i;

    if (left < heap->size && heap->arr[left].priority > heap->arr[maxIdx].priority) {
        maxIdx = left;
    }

    if (right < heap->size && heap->arr[right].priority > heap->arr[maxIdx].priority) {
        maxIdx = right;
    }

    if (maxIdx != i) {
        swap(&heap->arr[i], &heap->arr[maxIdx]);
        heapify(heap, maxIdx);
    }
}

Pair removeMax(MaxHeap* heap) {
    if (heap->size == 0) {
        return (Pair){-1, -1}; // or some error code
    }

    Pair data = heap->arr[0];
    
    // Swap the root with the last element
    heap->arr[0] = heap->arr[heap->size - 1];
    
    // Decrease heap size and shrink the array
    heap->size -= 1;
    heap->arr = realloc(heap->arr, heap->size * sizeof(Pair));

    // Heapify the root element to restore heap property
    heapify(heap, 0);

    return data;
}

int isEmpty(MaxHeap* heap) {
    return heap->size == 0;
}

void freeHeap(MaxHeap* heap) {
    free(heap->arr);
    free(heap);
}



void findPriorityScheduling(Process processes[], int n) {

    int remainingBurstTime[n];
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }
    
    MaxHeap* readyQueue = createHeap();
    add(readyQueue,processes[0].arrivalTime,processes[0].priority);
    int currTime = 0;
    int i = 1;
    while (!isEmpty(readyQueue)) 
    {
        Pair process  =  removeMax(readyQueue);

        if(remainingBurstTime[process.index] >0) {
            remainingBurstTime[process.index]--;
            currTime++;
        }
       

        for (; i < n; i++) {
            if(processes[i].arrivalTime <=currTime) {
                add(readyQueue,i,processes[i].priority);
            }else{
                break;
            }
        }

        if(remainingBurstTime[process.index] == 0) {
            processes[process.index].completionTime = currTime;
        }else if(remainingBurstTime[process.index] >0){
            add(readyQueue,process.index,process.priority);
        }

    }

    for (int k = 0; k < n; k++) {
        processes[k].turnaroundTime = processes[k].completionTime - processes[k].arrivalTime;
        processes[k].waitingTime = processes[k].turnaroundTime - processes[k].burstTime;
    }

    freeHeap(readyQueue);
    
 

}




void displayProcessDetailsForPriorityScheduling(Process processes[], int n, const char *algoName) {
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
            fprintf(outputFile, "| %7d  | %3d | %12d | %10d | %15d | %15d | %12d |\n",
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

void readFileForPriorityScheduling(const char *filename, int *numProcesses, int arrivalTime[], int burstTime[], int priority[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Reading the number of processes
    fscanf(file, "NoOfProcess = %d\n", numProcesses);

    // Reading the Priority
    fscanf(file, "Priority =");
    for (int i = 0; i < *numProcesses; i++) {
        fscanf(file, "%d", &priority[i]);
    }

    // Reading the ArrivalTime
    fscanf(file, "\nArrivalTime =");
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

void priorityScheduling() { //priorityScheduling
    char mode[25]; 
    Process *processes;
    int NoOfProcess;
    int *arrivalTime = (int *)malloc(100 * sizeof(int));  // Assume a maximum of 100 processes for simplicity
    int *burstTime = (int *)malloc(100 * sizeof(int));    // Adjust as needed
    int *priority = (int *)malloc(100 * sizeof(int));     // Adjust as needed

    readFileForPriorityScheduling("Test Cases/PriorityScheduling.txt", &NoOfProcess, arrivalTime, burstTime, priority);

    processes = (Process*) malloc(NoOfProcess * sizeof(Process));

    printf("%d", NoOfProcess);
    // Initialize the process array
    for (int i = 0; i < NoOfProcess; i++) {
        printf("%d ",burstTime[i]);
        processes[i].pid = i + 1;
        processes[i].arrivalTime = arrivalTime[i];
        processes[i].burstTime = burstTime[i];
        processes[i].priority = priority[i];
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }

    findPriorityScheduling(processes, NoOfProcess);


    displayProcessDetailsForPriorityScheduling(processes, NoOfProcess, "PriorityScheduling");

    free(arrivalTime);
    free(burstTime);
    free(priority); // Free priority array as well
    free(processes);

}
