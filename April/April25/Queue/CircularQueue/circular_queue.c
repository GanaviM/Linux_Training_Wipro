#include "circular_queue.h"

// Function to create a new circular queue with given capacity
struct CircularQueue* createCircularQueue(int capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if (queue->array == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = -1; // Initialize front and rear
    queue->size = 0; // Initialize size
    return queue;
}

// Function to check if the circular queue is full
bool isFull(struct CircularQueue* queue) {
    return (queue->size == queue->capacity);
}

// Function to check if the circular queue is empty
bool isEmpty(struct CircularQueue* queue) {
    return (queue->size == 0);
}

// Function to add an element to the rear of the circular queue (enqueue)
void enqueue(struct CircularQueue* queue, int data) {
    if (isFull(queue)) {
        printf("Queue overflow.\n");
        exit(EXIT_FAILURE);
    }
    queue->rear = (queue->rear + 1) % queue->capacity; // Move rear pointer circularly
    queue->array[queue->rear] = data; // Assign data to rear
    if (queue->front == -1) {
        queue->front = queue->rear; // If it's the first element, update front
    }
    queue->size++; // Increment size
    printf("%d enqueued to queue.\n", data);
}

// Function to remove an element from the front of the circular queue (dequeue)
int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow.\n");
        exit(EXIT_FAILURE);
    }
    int data = queue->array[queue->front]; // Get data from front
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1; // If it's the last element, reset front and rear
    } else {
        queue->front = (queue->front + 1) % queue->capacity; // Move front pointer circularly
    }
    queue->size--; // Decrement size
    return data;
}

// Function to return the front element of the circular queue
int front(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    return queue->array[queue->front];
}

// Function to return the rear element of the circular queue
int rear(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    return queue->array[queue->rear];
}
