#include <stdio.h>
#include <stdlib.h>

int fcfs() {
    int noOfProcesses;
    
    printf("Enter number of processes: ");
    scanf("%d", &noOfProcesses);

    int *arrival_time = (int *) malloc(noOfProcesses * sizeof(int));
    int *burst_time = (int *) malloc(noOfProcesses * sizeof(int));
    int *completion_time = (int *) malloc(noOfProcesses * sizeof(int));
    int *turn_around_time = (int *) malloc(noOfProcesses * sizeof(int));
    int *waiting_time = (int *) malloc(noOfProcesses * sizeof(int));
 
    // Check if memory allocation was successful
    if (arrival_time == NULL || burst_time == NULL || completion_time == NULL ||
        turn_around_time == NULL || waiting_time == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // Exit with error code
    }

    for (int i = 0; i < noOfProcesses; i++) {
        printf("Enter Arrival Time and Burst Time of pid%d\n",i);
        scanf("%d", &arrival_time[i]);
        scanf("%d", &burst_time[i]);
    }

    

    completion_time[0] = burst_time[0];
    for (int i = 1; i < noOfProcesses; i++) {
        completion_time[i] = arrival_time[i] < completion_time[i-1] ? completion_time[i-1] + burst_time[i] : arrival_time[i] + burst_time[i];
    }


    // find turn around time and burst time
    for (int i = 0; i < noOfProcesses; i++) {
        turn_around_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turn_around_time[i] - burst_time[i];
    }

    printf("Pid    Arrival Time    Burst Time    Completion Time    TAT    WT\n");
    for (int i = 0; i < noOfProcesses; i++) {
        printf("%d\t\t",i);
        printf("%d\t\t", arrival_time[i]);
        printf("%d\t", burst_time[i]);
        printf("%d\t\t", completion_time[i]);
        printf("%d\t", turn_around_time[i]);
        printf("%d\t\n", waiting_time[i]);
    }

    // Free
    free(arrival_time);
    free(burst_time);
    free(completion_time);
    free(turn_around_time);
    free(waiting_time);
 
    return 0;  
}

int main() {
    fcfs();
}