#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

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

void insertAtBeginning(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *headRef;
    *headRef = newNode;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void reverseList(struct Node** headRef) {
    struct Node *prev = NULL, *current = *headRef, *next;
    while (current != NULL) {
        next = current->next; 
        current->next = prev; 
        prev = current; 
	current = next;
    }
    *headRef = prev; 
}

int main() {
    struct Node* head = NULL;

   
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtBeginning(&head, 3);

   
    printf("Original linked list: ");
    printList(head);

    reverseList(&head);

    printf("Reversed linked list: ");
    printList(head);

    return 0;
}
