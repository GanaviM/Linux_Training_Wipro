#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tree.h"
#include "stack.h"

// Function to create a new tree node
struct TreeNode* createNode(char value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to build a binary expression tree from a postfix expression
struct TreeNode* buildTree(char* postfix) {
    struct TreeNode* stack[100]; // Assuming maximum 100 elements in the stack
    int top = -1;
    struct TreeNode *t, *t1, *t2;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            t = createNode(postfix[i]);
            stack[++top] = t;
        } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            t = createNode(postfix[i]);
            t1 = stack[top--];
            t2 = stack[top--];
            t->right = t1;
            t->left = t2;
            stack[++top] = t;
        }
    }
    return stack[top];
}

// Function to perform an iterative inorder traversal of a binary expression tree
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct TreeNode* current = root;
    struct StackNode* stack = NULL;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%c ", current->data);
        current = current->right;
    }
}

// Function to evaluate an expression tree
int evaluateExpression(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return root->data - '0';
    }

    int left_val = evaluateExpression(root->left);
    int right_val = evaluateExpression(root->right);

    switch (root->data) {
        case '+':
            return left_val + right_val;
        case '-':
            return left_val - right_val;
        case '*':
            return left_val * right_val;
        case '/':
            return left_val / right_val;
        default:
            return 0;
    }
}

// Function to deallocate memory for the tree nodes
void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
