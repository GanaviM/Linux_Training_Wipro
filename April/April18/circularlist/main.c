#include <stdio.h>
#include "cirlinklist.h"

int main() {
    
    Node* head = NULL;
    int i, val;
    for (i = 0; i < 5; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &val);
        head = insertNode(head, val);
    }

    int total = sumValues(head);
    printf("Sum of all values in the circular linked list: %d\n", total);

    return 0;
}
