#ifndef NODE_H
#define NODE_H

// Define the structure of a node in the linked list
typedef struct Node {
    int data;           // Data stored in the node
    struct Node *next;  // Pointer to the next node
} Node;

#endif
