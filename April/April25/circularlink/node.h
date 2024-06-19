#ifndef NODE_H
#define NODE_H

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function prototype for creating a new node
Node *createNode(int data);

#endif
