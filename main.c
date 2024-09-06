#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_scheduling_algo.h"

 


int main() {
    
    char AlgorithmName[25];

    FILE *algoName = fopen("Test Cases/AlgorithmName.txt", "r");

    if (algoName == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Reading the AlgorithmName
    fscanf(algoName, "AlgorithmName = %s\n", AlgorithmName);
    fclose(algoName);

    if (strcmp(AlgorithmName, "FirstComeFirstServe") == 0) {

        firstComeFirstServe();

    } else if (strcmp(AlgorithmName, "ShortestJobFirst") == 0) {
         
        shortestJobFirst();
        
     } else if (strcmp(AlgorithmName, "RoundRobin") == 0) {
         
        roundrobinTime();

    } else if (strcmp(AlgorithmName, "PriorityScheduling") == 0) {
        priorityScheduling();
    }

    return 0;
}
