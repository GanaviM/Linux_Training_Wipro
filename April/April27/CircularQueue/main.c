#include <stdio.h>
#include "circular_queue.h"

int main() {
    struct CircularQueue* queue = createCircularQueue(5); // Create a circular queue with capacity 5

    // Enqueue elements onto the circular queue
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);

    // Dequeue elements from the circular queue and print them
    printf("%d dequeued from queue.\n", dequeue(queue));
    printf("%d dequeued from queue.\n", dequeue(queue));

    // Enqueue elements again
    enqueue(queue, 60);
    enqueue(queue, 70);

    // Print front and rear elements of the circular queue
    printf("Front element of the queue: %d\n", front(queue));
    printf("Rear element of the queue: %d\n", rear(queue));

    // Dequeue remaining elements from the circular queue and print them
    while (!isEmpty(queue)) {
        printf("%d dequeued from queue.\n", dequeue(queue));
    }

    // Attempting to dequeue from an empty circular queue
    printf("%d dequeued from queue.\n", dequeue(queue)); // Queue underflow

    return 0;
}
