#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node.h"

// Function to create a new empty list
List *createList() {
    // Allocate memory for the list structure
    List *list = (List *)malloc(sizeof(List));
    // Check if memory allocation was successful
    if (list == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE); // Exit program if allocation fails
    }
    // Initialize the list with a NULL head pointer
    list->head = NULL;
    return list;
}

// Function to calculate the sum of all nodes in the list
int calculateSum(List *list) {
    int sum = 0;
    Node *current = list->head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}


// Function to insert a new node with the given data at the end of the list
void insertAtEnd(List *list, int data) {
    // Create a new node with the given data
    Node *newNode = createNode(data);
    // If the list is empty, set the new node as the head
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // Traverse the list to find the last node
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Insert the new node at the end
        temp->next = newNode;
    }
}

// Function to display the contents of the list
void displayList(List *list) {
    // Traverse the list and print each node's data
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to delete the entire list and free memory
void deleteList(List *list) {
    // Traverse the list and free memory for each node
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    // Free memory for the list structure itself
    free(list);
}
