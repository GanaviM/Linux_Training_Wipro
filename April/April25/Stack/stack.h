#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure of the stack node
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes for stack operations
struct Node* createNode(int data);
bool isEmpty(struct Node* root);
void push(struct Node** root, int data);
int pop(struct Node** root);
int peek(struct Node* root);

#endif
