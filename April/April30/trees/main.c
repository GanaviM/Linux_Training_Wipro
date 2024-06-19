#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h" // Include the header file containing binary tree functionality

int main() {
    struct Node* root = NULL;
    clock_t start, end; // Variables to store start and end time
    double cpu_time_used; // Variable to store CPU time used

    // Start clock
    start = clock();

    // Insert nodes into the binary tree
    root = insert(root, 55);
    insert(root, 23);
    insert(root, 15);
    insert(root, 40);
    insert(root, 70);
    insert(root, 63);
    insert(root, 35);

    // Print in-order traversal of the binary tree
    printf("In-order traversal: ");
    inOrder(root);
    printf("\n");

    // Calculate the sum of all nodes in the binary tree
    int sum = add(root);
    printf("Sum of all nodes: %d\n", sum);

    // Stop clock
    end = clock();

    // Calculate CPU time used
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);

    // Memory deallocation for the binary tree is not shown here to keep the example simple

    return 0;
}

