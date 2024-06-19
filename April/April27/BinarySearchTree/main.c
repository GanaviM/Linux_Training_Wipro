#include <stdio.h>
#include "binary_search.h"

int main() {
    struct node* root = NULL;

    // Insert some nodes into the BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");

    // Find and print the minimum and maximum values in the BST
    struct node* minNode = findMin(root);
    printf("Minimum value in the BST: %d\n", minNode->data);

    struct node* maxNode = findMax(root);
    printf("Maximum value in the BST: %d\n", maxNode->data);

    // Search for a key value in the BST
    int key = 70;
    if (search(root, key)) {
        printf("%d is found in the BST\n", key);
    } else {
        printf("%d is not found in the BST\n", key);
    }

    root = deleteNode(root, 70);
    printf("Inorder traversal after deleting node 70: ");
    inorderTraversal(root);
    printf("\n");

    deleteTree(root); // Free memory allocated for the BST nodes
    return 0;
}
