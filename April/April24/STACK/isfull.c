
#include "isfull.h"

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}
