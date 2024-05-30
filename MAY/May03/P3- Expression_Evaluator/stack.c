#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Function to create a new stack node
struct StackNode* createStackNode(struct TreeNode* treeNode) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

// Function to push a tree node onto the stack
void push(struct StackNode** top, struct TreeNode* treeNode) {
    struct StackNode* newNode = createStackNode(treeNode);
    newNode->next = *top;
    *top = newNode;
}

// Function to pop a tree node from the stack
struct TreeNode* pop(struct StackNode** top) {
    if (*top == NULL) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    struct TreeNode* treeNode = (*top)->treeNode;
    struct StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode* top) {
    return top == NULL;
}
