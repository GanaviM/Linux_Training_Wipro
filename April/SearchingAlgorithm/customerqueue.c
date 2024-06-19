#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    int id;
    struct Customer* next;
} Customer;

typedef struct Queue {
    Customer* front;
    Customer* rear;
} Queue;

Customer* createCustomer(int id) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    if (newCustomer == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newCustomer->id = id;
    newCustomer->next = NULL;
    return newCustomer;
}

Queue* initializeQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, int id) {
    Customer* newCustomer = createCustomer(id);
    if (isEmpty(queue)) {
        queue->front = newCustomer;
        queue->rear = newCustomer;
    } else {
        queue->rear->next = newCustomer;
        queue->rear = newCustomer;
    }
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. No customer to dequeue.\n");
        return -1;
    }
    Customer* dequeuedCustomer = queue->front;
    int dequeuedCustomerId = dequeuedCustomer->id;
    queue->front = dequeuedCustomer->next;
    free(dequeuedCustomer);
    return dequeuedCustomerId;
}

void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    Customer* current = queue->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d ", current->id);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Queue* queue = initializeQueue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    displayQueue(queue);

    int dequeuedId = dequeue(queue);
    if (dequeuedId != -1) {
        printf("Dequeued customer ID: %d\n", dequeuedId);
    }

    displayQueue(queue);

    Customer* current = queue->front;
    Customer* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(queue);

    return 0;
}
