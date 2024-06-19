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
        exit(EXIT_FAILURE);
    }
    // Initialize the node's data and next pointer
    newNode->data = data;
    newNode->next = NULL;
    // Return the newly created node
    return newNode;
}
