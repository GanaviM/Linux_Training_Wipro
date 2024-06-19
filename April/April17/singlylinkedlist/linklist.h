#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createLinkedList();
int sumLinkedList(Node *head);
void freeLinkedList(Node *head);

#endif
