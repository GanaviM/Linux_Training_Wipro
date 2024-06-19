#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure of the circular queue
struct CircularQueue {
    int *array; // Array to store queue elements
    int capacity; // Maximum capacity of the queue
    int front; // Index of the front element
    int rear; // Index of the rear element
    int size; // Current size of the queue
};

// Function prototypes for circular queue operations
struct CircularQueue* createCircularQueue(int capacity);
bool isFull(struct CircularQueue* queue);
bool isEmpty(struct CircularQueue* queue);
void enqueue(struct CircularQueue* queue, int data);
int dequeue(struct CircularQueue* queue);
int front(struct CircularQueue* queue);
int rear(struct CircularQueue* queue);

#endif
