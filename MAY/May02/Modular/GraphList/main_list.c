#include "graph.h"
#include <stdio.h>
#include <time.h> // Include time.h for clock() function

int main() {
    int numVertices = 4;
    
    // Record the start time
    clock_t start = clock();
    
    struct Graph* graph = createGraph(numVertices);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    
    printGraph(graph);
    
    // Record the end time
    clock_t end = clock();
    
    // Calculate CPU time
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // Print CPU time
    printf("CPU time used: %f seconds\n", cpu_time_used);
    
    return 0;
}
