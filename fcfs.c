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
    int *response_time = (int *) malloc(noOfProcesses * sizeof(int));

    // Check if memory allocation was successful
    if (arrival_time == NULL || burst_time == NULL || completion_time == NULL ||
        turn_around_time == NULL || waiting_time == NULL || response_time == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // Exit with error code
    }

    printf("Enter Arrival Time:\n");
    for (int i = 0; i < noOfProcesses; i++) {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter Burst Time:\n");
    for (int i = 0; i < noOfProcesses; i++) {
        scanf("%d", &burst_time[i]);
    }













    

    // Free
    free(arrival_time);
    free(burst_time);
    free(completion_time);
    free(turn_around_time);
    free(waiting_time);
    free(response_time);

    return 0;  
}

int main() {

}