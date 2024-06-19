#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Define a structure for the stack
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Function to create an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an item onto the stack
void push(struct Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->items[stack->top--];
}

int main() {
    char str[MAX_SIZE];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character

    // Create a stack
    struct Stack* stack = createStack();

    // Push characters of the string onto the stack
    for (int i = 0; i < strlen(str); i++) {
        push(stack, str[i]);
    }

    // Create an empty character array to hold the reversed string
    char reversedStr[MAX_SIZE];

    // Pop characters from the stack and store them in the reversed string array
    int index = 0;
    while (!isEmpty(stack)) {
        reversedStr[index++] = pop(stack);
    }
    reversedStr[index] = '\0';

    // Print the reversed string
    printf("Reversed string: %s\n", reversedStr);

    // Free the dynamically allocated memory for the stack
    free(stack);

    return 0;
}
