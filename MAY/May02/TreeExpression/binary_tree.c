#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "binary_tree.h"

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

TreeNode* buildTree(char* expression) {
    TreeNode* stack[100];
    int top = -1;

    TreeNode* root = NULL;
    for (int i = 0; expression[i]; i++) {
        if (expression[i] == ' ')
            continue;

        if (isdigit(expression[i]) || isalpha(expression[i])) {
            TreeNode* newNode = createNode(expression[i]);
            if (!newNode) {
                printf("Memory allocation failed!\n");
                exit(EXIT_FAILURE);
            }
            if (!root)
                root = newNode;
            else {
                TreeNode* right = stack[top--];
                TreeNode* left = stack[top--];
                newNode->left = left;
                newNode->right = right;
            }
            stack[++top] = newNode;
        } else {
            TreeNode* newNode = createNode(expression[i]);
            if (!newNode) {
                printf("Memory allocation failed!\n");
                exit(EXIT_FAILURE);
            }
            stack[++top] = newNode;
        }
    }

    return root;
}

int evaluate(TreeNode* root) {
    if (!root)
        return 0;

    // If the node is an operand, return its value
    if (isdigit(root->data) || isalpha(root->data))
        return root->data - '0';

    // Evaluate left and right subtrees
    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    // Perform operation based on operator
    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
        default: 
            printf("Error: Invalid operator %c\n", root->data);
            return 0;
    }
}

void freeTree(TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
