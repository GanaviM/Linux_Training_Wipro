#include <stdio.h>
#include <stdlib.h>
#include "pop.h"

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}
