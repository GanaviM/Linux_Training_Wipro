#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with numVertices vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    // Create an array of pointers to Node to represent adjacency lists
    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    // Initialize all adjacency lists as empty
    for (int i = 0; i < numVertices; ++i) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Create a new node for the destination vertex
    struct Node* newNode = createNode(dest);

    // Add the node to the front of the adjacency list of source vertex
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Function to print the graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        printf("\nAdjacency list of vertex %d\n head ", v);
        struct Node* temp = graph->adjLists[v];
        while (temp) {
            printf("-> %d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
