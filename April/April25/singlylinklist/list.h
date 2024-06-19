#include "node.h"

Node *createNode(int data);

// Define the structure of the linked list
typedef struct List {
    Node *head;  // Pointer to the head of the list
} List;

// Function prototypes for list operations
int calculateSum(List *list);
List *createList();
void insertAtEnd(List *list, int data);
void displayList(List *list);
void deleteList(List *list);
