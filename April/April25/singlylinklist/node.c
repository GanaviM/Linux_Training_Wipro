#include <stdio.h>
#include <stdlib.h>
#include "node.h"

// Function to create a new node with the given data
Node *createNode(int data) {
    // Allocate memory for the new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    // Check if memory allocation was successful
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // Exit program if allocation fails
    }
    // Initialize the node with the provided data and NULL next pointer
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
