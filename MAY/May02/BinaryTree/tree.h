#ifndef TREE_H
#define TREE_H

// Structure to represent a node in the binary expression tree
struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function prototypes
struct TreeNode* createNode(char value);
struct TreeNode* buildTree(char* postfix);
void inorderTraversal(struct TreeNode* root);
int evaluateExpression(struct TreeNode* root);
void freeTree(struct TreeNode* root);

#endif
