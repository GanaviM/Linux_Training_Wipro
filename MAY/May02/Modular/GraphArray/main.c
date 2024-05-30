#include<stdio.h>
#include "graph.h"
#include <time.h> // Include time.h for clock() function

int main() {
    int numVertices = 4;
 
    // Record the start time
    clock_t start = clock();
 
    initializeGraph(numVertices);
 
    addEdge(0, 1); // Directed edge from 0 to 1
    addEdge(1, 2); // Directed edge from 1 to 2
    addEdge(2, 3); // Directed edge from 2 to 3
 
    printGraph(numVertices);
 
    // Record the end time
    clock_t end = clock();
 
    // Calculate CPU time
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 
    // Print CPU time
    printf("CPU time used: %f seconds\n", cpu_time_used);
 
    return 0;
}

