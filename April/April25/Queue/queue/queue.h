#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure of the queue node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure of the queue
struct Queue {
    struct Node *front, *rear;
};

// Function prototypes for queue operations
struct Node* createNode(int data);
struct Queue* createQueue();
bool isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, int data);
int dequeue(struct Queue* queue);

#endif
