#ifndef BST_H  // Header guard to prevent multiple inclusion of the header
#define BST_H

#include <stdbool.h>  // Include the standard library for boolean data type

// Node structure for BST
typedef struct Node {
    int data;  // Data stored in the node
    struct Node* left;  // Pointer to the left child node
    struct Node* right;  // Pointer to the right child node
} Node;  // Definition of the Node structure

// Function declarations
Node* createNode(int data);  // Function to create a new node
Node* insert(Node* root, int data);  // Function to insert a node in the BST
Node* deleteNode(Node* root, int data);  // Function to delete a node from the BST
Node* search(Node* root, int data);  // Function to search for a node in the BST
void inorderTraversal(Node* root);  // Function to perform in-order traversal of the BST
void preorderTraversal(Node* root);  // Function to perform pre-order traversal of the BST
void postorderTraversal(Node* root);  // Function to perform post-order traversal of the BST
bool isBST(Node* root);  // Function to check if the binary tree is a BST
int maxHeight(Node* root);  // Function to find the maximum height of the binary tree
void findMinMax(Node* root, int* min, int* max);  // Function to find the minimum and maximum values in the binary tree

#endif /* BST_H */  // End of header guard directive
