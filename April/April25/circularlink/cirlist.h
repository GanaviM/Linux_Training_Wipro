#ifndef LIST_H
#define LIST_H

#include "node.h"

// Circular linked list structure
typedef struct {
    Node *head;
} CircularList;

// Function prototypes
CircularList *createCircularList();
void insertAtEnd(CircularList *list, int data);
void displayList(CircularList *list);
void deleteList(CircularList *list);

#endif
