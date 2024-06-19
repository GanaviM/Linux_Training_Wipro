#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new node
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Function to insert a new node into the BST
struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to search for a node with a given data in the BST
int search(struct node* root, int data) {
    if (root == NULL) {
        return 0;
    } else if (root->data == data) {
        return 1;
    } else if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Function to perform an in-order traversal of the BST
void inorderTraversal(struct node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
