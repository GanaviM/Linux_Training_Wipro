#ifndef DOUBLYLINKLIST_H
#define DOUBLYLINKLIST_H

#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the doubly linked list
typedef struct Node {
    int data;           // Data stored in the node
    struct Node* prev;  // Pointer to the previous node
    struct Node* next;  // Pointer to the next node
} Node;

// Function prototypes for the doubly linked list operations
Node* createNode(int data);
Node* insertNode(Node* head, int data);
void displayListForward(Node* head);
void displayListBackward(Node* tail);
void freeList(Node* head);

#endif
