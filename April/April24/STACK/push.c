#include <stdio.h>
#include <stdlib.h>
#include "push.h"

void push(Stack *stack, int item) {
    if (isFull(stack)) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->array[++stack->top] = item;
}
