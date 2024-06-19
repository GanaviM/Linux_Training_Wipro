#include <stdio.h>
#include "stack.h"

int main() {
    struct Node* root = NULL; // Initialize the stack

    // Push elements onto the stack
    push(&root, 10);
    push(&root, 20);
    push(&root, 30);

    // Print the top element of the stack
    printf("Top element of the stack: %d\n", peek(root));

    // Pop elements from the stack and print them
    printf("Popped from stack: %d\n", pop(&root));
    printf("Popped from stack: %d\n", pop(&root));
    printf("Popped from stack: %d\n", pop(&root));

    // Attempting to pop from an empty stack
    printf("Popped from stack: %d\n", pop(&root)); // Stack underflow

    return 0;
}
