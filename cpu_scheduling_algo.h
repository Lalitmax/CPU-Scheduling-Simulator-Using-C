#ifndef CPU_SCHEDULING_ALGO_H
 


typedef struct Process {
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
} Process;





void firstComeFirstServe(Process processes[], int n);
void roundrobinTime(Process processes[], int n, int qt);
void findSJFWithPreemptive(Process proc[], int n);
void findSJFWithNonPreemptive(Process proc[], int n);
void priorityScheduling(Process processes[], int n);

#endif



 