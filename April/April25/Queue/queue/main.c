#include <stdio.h>
#include "queue.h"

int main() {
    struct Queue* queue = createQueue(); // Create an empty queue

    // Enqueue elements onto the queue
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    // Dequeue elements from the queue and print them
    printf("%d dequeued from queue.\n", dequeue(queue));
    printf("%d dequeued from queue.\n", dequeue(queue));
    printf("%d dequeued from queue.\n", dequeue(queue));

    // Attempting to dequeue from an empty queue
    printf("%d dequeued from queue.\n", dequeue(queue)); // Queue underflow

    return 0;
}
