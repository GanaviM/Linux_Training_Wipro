#include <stdlib.h>
#include "linklist.h"

Node* createLinkedList() {
    Node *head = NULL;
    Node *temp = NULL;
    Node *prev = NULL;
    
    for (int i = 1; i <= 5; i++) {
        temp = (Node *)malloc(sizeof(Node));
        if (temp == NULL) {
            exit(EXIT_FAILURE);
        }
        temp->data = i;
        temp->prev = prev;
        temp->next = NULL;
        
        if (prev != NULL) {
            prev->next = temp;
        } else {
            head = temp;
        }
        
        prev = temp;
    }
    
    return head;
}

int sumLinkedList(Node *head) {
    int sum = 0;
    Node *p = head;
    
    while (p != NULL) {
        sum += p->data;
        p = p->next;
    }
    
    return sum;
}

void freeLinkedList(Node *head) {
    Node *temp;
    
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
