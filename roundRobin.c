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
bool isEmpty() {
    return N == 0;
}

// Push a process index to the queue
void push(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty()) {
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
    if (isEmpty()) return INT_MAX;  // Error case
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

void roundrobinTime(Process Processes[], int n, int qt) {
    int remainingBurstTime[n];
    
    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = Processes[i].burstTime;
    }

    push(0);  // Push the first process
    int currTime = Processes[0].arrivalTime;  // Start at the first process arrival time
    int i = 1;  // Start tracking the second process

    while (!isEmpty()) {
        int currProcessidx = pop();

        // Process execution
        if (remainingBurstTime[currProcessidx] >= qt) {
            remainingBurstTime[currProcessidx] -= qt;
            currTime += qt;
        } else {
            currTime += remainingBurstTime[currProcessidx];
            remainingBurstTime[currProcessidx] = 0;
        }

        // Check if new processes have arrived while the current one was executing
        while (i < n && Processes[i].arrivalTime <= currTime) {
            push(i);
            i++;
        }

        // Re-add the current process if it hasn't finished
        if (remainingBurstTime[currProcessidx] > 0) {
            push(currProcessidx);
        } else {
            // Process is finished, set completion time
            Processes[currProcessidx].completionTime = currTime;
        }

        // If the queue is empty but there are still processes that haven't arrived,
        // move the current time to the arrival time of the next process
        if (isEmpty() && i < n) {
            currTime = Processes[i].arrivalTime;
            push(i);
            i++;
        }
    }

    // Calculate turnaround time and waiting time for each process
    for (int i = 0; i < n; i++) {
        Processes[i].turnaroundTime = Processes[i].completionTime - Processes[i].arrivalTime;
        Processes[i].waitingTime = Processes[i].turnaroundTime - Processes[i].burstTime;
    }
}