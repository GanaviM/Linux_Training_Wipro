#include "binary_tree.h"
#include <stdio.h>

int main() {
    struct node* root = NULL;

    // Insert some values into the BST
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);

    // Perform in-order traversal
    printf("In-order traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Search for specific values
    printf("Searching for 7: %s\n", search(root, 7) ? "Found" : "Not found");
    printf("Searching for 12: %s\n", search(root, 12) ? "Found" : "Not found");

    return 0;
}
