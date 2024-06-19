#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

typedef struct {
    int top;
    int items[MAX_SIZE];
} Stack;

void push(Stack *s, int value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->top++;
    s->items[s->top] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    int popped = s->items[s->top];
    s->top--;
    return popped;
}

int main() {
    // Start the clock
    clock_t start = clock();

    // Unrolled Loop for Stack Operations
    Stack stack;
    stack.top = -1;
    for (int i = 0; i < MAX_SIZE; i += 2) {
        push(&stack, i);
        if (i + 1 < MAX_SIZE) {
            push(&stack, i + 1);
        }
    }
    for (int i = 0; i < MAX_SIZE; i += 2) {
        pop(&stack);
        if (i + 1 < MAX_SIZE) {
            pop(&stack);
        }
    }

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_unrolled = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken for stack operations (Unrolled Loop): %f seconds\n", time_taken_unrolled);

    return 0;
}
