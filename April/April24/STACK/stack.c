#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->array = (int *)malloc(capacity * sizeof(int));
    if (stack->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

void destroyStack(Stack *stack) {
    free(stack->array);
    free(stack);
}
