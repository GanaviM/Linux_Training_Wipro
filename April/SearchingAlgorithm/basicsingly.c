#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *headRef;
    *headRef = newNode;
}

// Function to insert a new node at the end of the list
void insertAtEnd(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* temp = *headRef;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete a node with a given value
void deleteNode(struct Node** headRef, int key) {
    struct Node *temp = *headRef, *prev = NULL;
    if (temp != NULL && temp->data == key) {
        *headRef = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Node* head = NULL;

    // Insertion operations
    insertAtEnd(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);

    // Print the linked list
    printf("Linked list after insertion: ");
    printList(head);

    // Deletion operation
    deleteNode(&head, 3);

    // Print the linked list after deletion
    printf("Linked list after deletion: ");
    printList(head);

    return 0;
}
