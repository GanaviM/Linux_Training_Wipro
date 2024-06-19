#include <stdio.h>
#include <stdlib.h>
#include "cirlinklist.h"

Node* insertNode(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (head == NULL) {
        newNode->next = newNode;
        return newNode;
    }
    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

int sumValues(Node* head) {
    if (head == NULL)
        return 0;
    int sum = 0;
    Node* temp = head;
    do {
        sum += temp->data;
        temp = temp->next;
    } while (temp != head);
    return sum;
}
