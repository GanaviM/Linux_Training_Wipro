#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "push.h"
#include "pop.h"

int main() {
    int choice, item;
    Stack *stack = createStack(5);

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull(stack)) {
                    printf("Stack full\n");
                } else {
                    printf("Enter element to push: ");
                    scanf("%d", &item);
                    push(stack, item);
                }
                break;
            case 2:
                if (isEmpty(stack)) {
                    printf("Stack empty\n");
                } else {
                    printf("Popped element: %d\n", pop(stack));
                }
                break;
            case 3:
                destroyStack(stack);
                printf("Exiting program\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
