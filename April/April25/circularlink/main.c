#include <stdio.h>
#include "cirlist.h"

int main() {
    // Create a new empty circular list
    CircularList *list = createCircularList();

    // Insert some data into the list
    insertAtEnd(list, 1);
    insertAtEnd(list, 2);
    insertAtEnd(list, 3);

    // Display the contents of the list
    printf("Circular List: ");
    displayList(list);

    // Delete the list and free memory
    deleteList(list);

    return 0;
}
