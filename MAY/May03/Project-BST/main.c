#include <stdio.h>  // Include standard I/O functions
#include <stdlib.h>  // Include standard library functions
#include <time.h>  // Include time functions
#include <limits.h>  // Include library for INT_MIN and INT_MAX
#include "bst.h"  // Include the header file defining the structures and function prototypes

int main() {
    Node* root = NULL;  // Declare a pointer to the root node and initialize it to NULL
    root = insert(root, 50);  // Insert nodes into the BST
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal: ");  // Print the result of inorder traversal
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");  // Print the result of preorder traversal
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");  // Print the result of postorder traversal
    postorderTraversal(root);
    printf("\n");

    int value = 70;  // Value to be searched in the BST
    Node* found = search(root, value);  // Search for the value in the BST
    if (found)
        printf("%d is found in the tree.\n", value);  // Print if the value is found
    else
        printf("%d is not found in the tree.\n", value);  // Print if the value is not found

    int min = INT_MAX, max = INT_MIN;  // Initialize variables to store min and max values
    findMinMax(root, &min, &max);  // Find the minimum and maximum values in the BST
    printf("Minimum value: %d\n", min);  // Print the minimum value
    printf("Maximum value: %d\n", max);  // Print the maximum value

    printf("Is the binary tree a BST? %s\n", isBST(root) ? "Yes" : "No");  // Check if the binary tree is a BST

    printf("Height of the binary tree: %d\n", maxHeight(root));  // Print the height of the binary tree

    // CPU time calculation
    clock_t start = clock();  // Start the clock
    // Perform some CPU intensive task here
    clock_t end = clock();  // End the clock
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  // Calculate CPU time used
    printf("CPU Time: %f seconds\n", cpu_time_used);  // Print CPU time used

    return 0;  // Return 0 to indicate successful completion of the program
}
