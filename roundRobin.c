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

bool isEmpty() {
    return N == 0;
}

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

int pop() {
    if (isEmpty()) return INT_MAX;
    Node *temp = head;
    head = head->next;
    int currData = temp->data;
    N--;
    free(temp);
    return currData;
}

int peek() {
    if (isEmpty()) return INT_MAX;
    return head->data;
}

typedef struct process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} process;

void findRoundrobinTime(process processes[], int n, int tq) {
    int remainingBurstTime[n];
    
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }
    
    push(0);
    int currTime = processes[0].arrivalTime;
    int i = 1;

    while (!isEmpty()) {
        int currprocessidx = pop();

        if (remainingBurstTime[currprocessidx] >= tq) {
            remainingBurstTime[currprocessidx] -= tq;
            currTime += tq;
        } else {
            int howmuchBurstTime = remainingBurstTime[currprocessidx];
            remainingBurstTime[currprocessidx] = 0;
            currTime += howmuchBurstTime;
        }

        for (; i < n; i++) {
            if (processes[i].arrivalTime <= currTime) {
                push(i);
            } else {
                break;
            }
        }

        if (remainingBurstTime[currprocessidx] != 0) {
            push(currprocessidx);
        } else if (remainingBurstTime[currprocessidx] == 0) {
            processes[currprocessidx].completionTime = currTime;
        }
    }

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter PID for process %d: ", i + 1);
        scanf("%d", &processes[i].pid);
        printf("Enter Arrival Time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("\n");
    }

    int timeQuantum;
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    findRoundrobinTime(processes, n, timeQuantum);

    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].pid, 
                processes[i].arrivalTime, 
                processes[i].burstTime, 
                processes[i].completionTime, 
                processes[i].turnaroundTime, 
                processes[i].waitingTime);
    }

    return 0;
}
