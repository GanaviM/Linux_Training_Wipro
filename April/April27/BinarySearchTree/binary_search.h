#ifndef BST_H
#define BST_H

// Structure to represent a node in the Binary Search Tree (BST)
struct node {
    int data;           // Integer value stored in the node
    struct node* left;  // Pointer to the left child node
    struct node* right; // Pointer to the right child node
};

// Function prototypes
struct node* createNode(int data);      // Create a new node
struct node* insert(struct node* root, int data); // Insert a node into the BST
int search(struct node* root, int data); // Search for a node with the given data
void inorderTraversal(struct node* root);// Perform inorder traversal of the BST
void deleteTree(struct node* root);     // Delete the entire BST
struct node* findMin(struct node* root);// Find the node with the minimum value in the BST
struct node* findMax(struct node* root);// Find the node with the maximum value in the BST
struct node* deleteNode(struct node* root, int data); // Delete a node with the given data from the BST

#endif /* BST_H */
