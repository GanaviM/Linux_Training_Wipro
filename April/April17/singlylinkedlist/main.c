#include <stdio.h>
#include "linklist.h"

int main() {
    Node *head = createLinkedList();
    int sum = sumLinkedList(head);
    printf("Sum of all values: %d\n", sum);
    freeLinkedList(head);
    return 0;
}
