#include <stdio.h>
#include <stdlib.h>
#include "cirlist.h"

// Function to create a new circular linked list
CircularList *createCircularList() {
    // Allocate memory for the circular list structure
    CircularList *list = (CircularList *)malloc(sizeof(CircularList));
    // Check if memory allocation was successful
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Initialize the head pointer to NULL (empty list)
    list->head = NULL;
    // Return the newly created circular list
    return list;
}

// Function to insert a new node with the given data at the end of the circular list
void insertAtEnd(CircularList *list, int data) {
    // Create a new node with the given data
    Node *newNode = createNode(data);
    // If the list is empty, set the new node as the head and point to itself (circular)
    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode;
    } else {
        // Otherwise, traverse to the end of the list and insert the new node
        Node *temp = list->head;
        while (temp->next != list->head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = list->head;
    }
}

// Function to display the contents of the circular list
void displayList(CircularList *list) {
    // If the list is empty, print a message and return
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    // Iterate through the list and print each node's data
    Node *current = list->head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head); // Stop when we reach the head again (circular)
    printf("\n");
}

// Function to delete the entire circular list and free memory
void deleteList(CircularList *list) {
    // If the list is empty, free the list structure and return
    if (list->head == NULL) {
        free(list);
        return;
    }
    // Otherwise, traverse the list and free each node
    Node *current = list->head;
    Node *next;
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != list->head); // Stop when we reach the head again (circular)
    // Free the list structure itself
    free(list);
}
