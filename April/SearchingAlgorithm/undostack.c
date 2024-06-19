#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Define a structure for a stack node
struct StackNode {
    char *state;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createNode(char *state) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->state = strdup(state);
    newNode->next = NULL;
    return newNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode* root) {
    return (root == NULL);
}

// Function to push a state onto the stack
void push(struct StackNode** root, char *state) {
    struct StackNode* newNode = createNode(state);
    newNode->next = *root;
    *root = newNode;
}

// Function to pop a state from the stack
char* pop(struct StackNode** root) {
    if (isEmpty(*root)) {
        printf("Stack underflow.\n");
        exit(1);
    }
    struct StackNode* temp = *root;
    *root = (*root)->next;
    char* popped = temp->state;
    free(temp);
    return popped;
}

// Function to simulate text editing and undo functionality
void textEditor() {
    struct StackNode* undoStack = NULL;
    char currentState[MAX_SIZE];
    currentState[0] = '\0'; // Initialize to empty string

    char input[MAX_SIZE];
    while (1) {
        printf("Enter text (or 'undo' to revert): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

        if (strcmp(input, "undo") == 0) {
            if (!isEmpty(undoStack)) {
                char* prevState = pop(&undoStack);
                strcpy(currentState, prevState);
                free(prevState);
                printf("Undo successful. Current text: %s\n", currentState);
            } else {
                printf("Nothing to undo.\n");
            }
        } else {
            push(&undoStack, currentState);
            strcpy(currentState, input);
            printf("Text entered. Current text: %s\n", currentState);
        }
    }
}

int main() {
    textEditor();
    return 0;
}
