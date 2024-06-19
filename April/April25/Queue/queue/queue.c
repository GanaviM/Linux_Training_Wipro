#include "queue.h"

// Function to create a new node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
bool isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to add an element to the rear of the queue (enqueue)
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("%d enqueued to queue.\n", data);
}

// Function to remove an element from the front of the queue (dequeue)
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow.\n");
        exit(EXIT_FAILURE);
    }
    struct Node* temp = queue->front;
    int dequeued = temp->data;
    queue->front = queue->front->next;
    free(temp);
    // If front becomes NULL, then make rear also NULL
    if (queue->front == NULL)
        queue->rear = NULL;
    return dequeued;
}
