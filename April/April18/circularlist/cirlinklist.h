#ifndef CIRLINKLIST_H
#define CIRLINKLIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* insertNode(Node* head, int data);
int sumValues(Node* head);

#endif
