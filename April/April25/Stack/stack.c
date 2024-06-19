#include "stack.h"

// Function to create a new node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the stack is empty
bool isEmpty(struct Node* root) {
    return root == NULL;
}

// Function to push an element onto the stack
void push(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *root;
    *root = newNode;
    printf("%d pushed to stack.\n", data);
}

// Function to pop an element from the stack
int pop(struct Node** root) {
    if (isEmpty(*root)) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    struct Node* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// Function to return the top element of the stack
int peek(struct Node* root) {
    if (isEmpty(root)) {
        printf("Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return root->data;
}
