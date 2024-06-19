#ifndef BST_H
#define BST_H

// Structure for a node in the BST
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Function prototypes
struct node* createNode(int data);
struct node* insert(struct node* root, int data);
int search(struct node* root, int data);
void inorderTraversal(struct node* root);

#endif
