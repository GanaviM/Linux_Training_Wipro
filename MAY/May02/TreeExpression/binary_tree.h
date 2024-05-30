#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(char data);
TreeNode* buildTree(char* expression);
int evaluate(TreeNode* root);
void freeTree(TreeNode* root);

#endif /* BINARY_TREE_H */
