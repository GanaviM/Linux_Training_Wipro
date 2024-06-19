#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new node
struct Node* createNode(int data) {
    // Allocate memory for the new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // Check if memory allocation is successful
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // Initialize the new node with given data and NULL left and right pointers
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary tree
struct Node* insert(struct Node* root, int data) {
    // Base case: If the tree is empty, create a new root node
    if (root == NULL) {
        return createNode(data);
    }

    // If the data to be inserted is smaller than the root, insert into the left subtree
    if (data < root->data) {
        root->left = insert(root->left, data);
    } 
    // If the data to be inserted is larger than the root, insert into the right subtree
    else if (data > root->data) {
        root->right = insert(root->right, data);
    } 
    // If the data already exists in the tree, handle duplicates (optional)
    else {
        // printf("Duplicate value: %d\n", data);
    }

    return root; // Return the (potentially modified) root node
}

// Function to perform in-order traversal of the binary tree
void inOrder(struct Node* root) {
    // Base case: If the current node is NULL, return
    if (root == NULL) {
        return;
    }
    // Visit left subtree
    inOrder(root->left);
    // Visit current node
    printf("%d ", root->data);
    // Visit right subtree
    inOrder(root->right);
}

// Function to calculate the sum of all nodes in the binary tree
int add(struct Node* root) {
    // Base case: If the current node is NULL, return 0
    if (root == NULL) {
        return 0;
    }
    // Recursively sum nodes in the left subtree, current node, and nodes in the right subtree
    return root->data + add(root->left) + add(root->right);
}
