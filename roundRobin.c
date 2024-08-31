#include <stdio.h>

stypedef truct Process {
    int pid;        // Process ID
    int burst_time; // Burst Time
    int remaining_time; // Remaining Time
}Process;

 void roundRobin( Process proc[], int n, int quantum) {
    int time = 0; 
    int done = 0;  

 
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                // If remaining time is greater than quantum
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                }
                // If remaining time is less than or equal to quantum
                else if{
                    time += proc[i].remaining_time;
                    proc[i].remaining_time = 0;
                    done++;
                    printf("Process %d finished at time %d\n", proc[i].pid, time);
                }
            }
        }
    }
}

int main() {
    int n;  
    int quantum;  

    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

     Process proc[n];

     
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
    }

    
    roundRobin(proc, n, quantum);

    return 0;
}
