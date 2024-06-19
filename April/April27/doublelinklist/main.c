#include <stdio.h>
#include "doublylinklist.h"

int main() {
    Node* head = NULL; // Initialize the head of the list to NULL

    // Insert some elements into the list
    head = insertNode(head, 1);
    head = insertNode(head, 2);
    head = insertNode(head, 3);

    // Display the elements of the list forward
    displayListForward(head);

    // Display the elements of the list backward
    Node* tail = head;
    while (tail->next != NULL) { // Traverse to the end of the list
        tail = tail->next;
    }
    displayListBackward(tail);

    // Free the memory allocated for the list
    freeList(head);

    return 0;
}
