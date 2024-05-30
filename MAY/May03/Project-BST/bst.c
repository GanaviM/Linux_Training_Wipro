#include "bst.h"  // Include the header file defining the structures and function prototypes
#include <stdio.h>  // Include standard I/O functions
#include <stdlib.h>  // Include standard library functions
#include <limits.h>  // Include library for INT_MIN and INT_MAX

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for the new node
    newNode->data = data;  // Assign the data to the new node
    newNode->left = newNode->right = NULL;  // Set left and right child pointers to NULL
    return newNode;  // Return the newly created node
}

// Function to insert a node with the given data into the BST
Node* insert(Node* root, int data) {
    if (root == NULL)  // If the root is NULL, create a new node and return it
        return createNode(data);
    if (data < root->data)  // If data is less than the root's data, insert into the left subtree
        root->left = insert(root->left, data);
    else if (data > root->data)  // If data is greater than the root's data, insert into the right subtree
        root->right = insert(root->right, data);
    return root;  // Return the root of the modified BST
}

// Function to delete a node with the given data from the BST
Node* deleteNode(Node* root, int data) {
    if (root == NULL)  // If the root is NULL, return NULL
        return root;
    if (data < root->data)  // If data is less than the root's data, delete from the left subtree
        root->left = deleteNode(root->left, data);
    else if (data > root->data)  // If data is greater than the root's data, delete from the right subtree
        root->right = deleteNode(root->right, data);
    else {  // If the node to be deleted is found
        if (root->left == NULL) {  // If the node has no left child
            Node* temp = root->right;  // Store the right child temporarily
            free(root);  // Free the memory occupied by the node
            return temp;  // Return the right child to connect with the parent
        } else if (root->right == NULL) {  // If the node has no right child
            Node* temp = root->left;  // Store the left child temporarily
            free(root);  // Free the memory occupied by the node
            return temp;  // Return the left child to connect with the parent
        }
        // If the node has both left and right children
        Node* temp = root->right;  // Find the minimum node in the right subtree
        while (temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;  // Copy the data of the minimum node to the current node
        root->right = deleteNode(root->right, temp->data);  // Delete the minimum node from the right subtree
    }
    return root;  // Return the root of the modified BST
}

// Function to search for a node with the given data in the BST
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data)  // If root is NULL or data is found at the root, return root
        return root;
    if (data < root->data)  // If data is less than the root's data, search in the left subtree
        return search(root->left, data);
    return search(root->right, data);  // If data is greater than the root's data, search in the right subtree
}

// Function to perform in-order traversal of the BST
void inorderTraversal(Node* root) {
    if (root != NULL) {  // If the root is not NULL
        inorderTraversal(root->left);  // Recursively traverse the left subtree
        printf("%d ", root->data);  // Print the data of the current node
        inorderTraversal(root->right);  // Recursively traverse the right subtree
    }
}

// Function to perform pre-order traversal of the BST
void preorderTraversal(Node* root) {
    if (root != NULL) {  // If the root is not NULL
        printf("%d ", root->data);  // Print the data of the current node
        preorderTraversal(root->left);  // Recursively traverse the left subtree
        preorderTraversal(root->right);  // Recursively traverse the right subtree
    }
}

// Function to perform post-order traversal of the BST
void postorderTraversal(Node* root) {
    if (root != NULL) {  // If the root is not NULL
        postorderTraversal(root->left);  // Recursively traverse the left subtree
        postorderTraversal(root->right);  // Recursively traverse the right subtree
        printf("%d ", root->data);  // Print the data of the current node
    }
}

// Utility function to check if the binary tree rooted at the given node is a BST
bool isBSTUtil(Node* root, int min, int max) {
    if (root == NULL)  // If the root is NULL, it's a BST
        return true;
    if (root->data < min || root->data > max)  // If the data of the root is outside the valid range, not a BST
        return false;
    // Check recursively for left and right subtrees
    return isBSTUtil(root->left, min, root->data - 1) && isBSTUtil(root->right, root->data + 1, max);
}

// Function to check if the binary tree is a BST
bool isBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);  // Call utility function with initial range as INT_MIN and INT_MAX
}

// Function to find the maximum height of the binary tree
int maxHeight(Node* root) {
    if (root == NULL)  // If the root is NULL, height is 0
        return 0;
    // Calculate heights of left and right subtrees recursively
    int leftHeight = maxHeight(root->left);
    int rightHeight = maxHeight(root->right);
    // Return the maximum of the heights plus 1 (for the current node)
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function to find the minimum and maximum values in the binary tree
void findMinMax(Node* root, int* min, int* max) {
    if (root == NULL)  // If the root is NULL, return
        return;
    findMinMax(root->left, min, max);  // Recursively find min/max in the left subtree
    if (root->data < *min)  // Update min if the data of the current node is smaller
        *min = root->data;
    if (root->data > *max)  // Update max if the data of the current node is larger
        *max = root->data;
    findMinMax(root->right, min, max);  // Recursively find min/max in the right subtree
}
