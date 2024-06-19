#include "doublylinklist.h"

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    if (newNode != NULL) { // Check if memory allocation was successful
        newNode->data = data; // Set the data of the new node
        newNode->prev = NULL; // Initialize the prev pointer to NULL
        newNode->next = NULL; // Initialize the next pointer to NULL
    }
    return newNode; // Return the pointer to the new node
}

// Function to insert a new node at the end of the list
Node* insertNode(Node* head, int data) {
    Node* newNode = createNode(data); // Create a new node
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return head; // Return the current head if memory allocation fails
    }
    if (head == NULL) { // If list is empty, new node becomes head
        return newNode;
    }
    Node* current = head;
    while (current->next != NULL) { // Traverse to the end of the list
        current = current->next;
    }
    current->next = newNode; // Link new node at the end
    newNode->prev = current; // Set previous pointer of new node
    return head; // Return the head of the list
}

// Function to display the elements of the list forward
void displayListForward(Node* head) {
    printf("List (Forward): ");
    while (head != NULL) { // Traverse the list forward
        printf("%d -> ", head->data); // Print the data of the current node
        head = head->next; // Move to the next node
    }
    printf("NULL\n");
}

// Function to display the elements of the list backward
void displayListBackward(Node* tail) {
    printf("List (Backward): ");
    while (tail != NULL) { // Traverse the list backward
        printf("%d -> ", tail->data); // Print the data of the current node
        tail = tail->prev; // Move to the previous node
    }
    printf("NULL\n");
}

// Function to free the memory allocated for the list
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) { // Traverse the list
        Node* temp = current; // Store the current node in a temporary variable
        current = current->next; // Move to the next node
        free(temp); // Free the memory of the current node
    }
}
