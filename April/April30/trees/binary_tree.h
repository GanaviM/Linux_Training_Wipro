#ifndef BINARY_TREE_H
#define BINARY_TREE_H

// Structure definition for a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function prototypes
struct Node* createNode(int data); // Function to create a new node
struct Node* insert(struct Node* root, int data); // Function to insert a node into the binary tree
void inOrder(struct Node* root); // Function to perform in-order traversal of the binary tree
int add(struct Node* root); // Function to calculate the sum of all nodes in the binary tree

#endif /* BINARY_TREE_H */
