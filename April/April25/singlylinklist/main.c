#include <stdio.h>
#include "list.h"

int main() {
    // Create a new empty list
    List *list = createList();

    // Insert some data into the list
    insertAtEnd(list, 1);
    insertAtEnd(list, 2);
    insertAtEnd(list, 3);

    // Display the contents of the list
    printf("Linked List: ");
    displayList(list);

    // Calculate the sum of all nodes in the list
    int sum = calculateSum(list);
    printf("Sum of all nodes: %d\n", sum);

    // Delete the list and free memory
    deleteList(list);

    return 0;
}
