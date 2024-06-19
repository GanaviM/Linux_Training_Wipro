#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int *array;
    int capacity;
    int top;
} Stack;

Stack *createStack(int capacity);
void destroyStack(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);

#endif
