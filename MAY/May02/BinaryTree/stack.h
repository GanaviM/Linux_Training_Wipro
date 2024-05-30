#ifndef STACK_H
#define STACK_H

#include "tree.h"

// Structure to represent a node in the stack
struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
};

// Function prototypes
struct StackNode* createStackNode(struct TreeNode* treeNode);
void push(struct StackNode** top, struct TreeNode* treeNode);
struct TreeNode* pop(struct StackNode** top);
int isEmpty(struct StackNode* top);

#endif
