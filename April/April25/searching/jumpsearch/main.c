#include <stdio.h>
#include "jump_search.h"

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90}; // Example sorted array
    int size = sizeof(array) / sizeof(array[0]); // Calculate the size of the array
    int target = 70; // Example target value to search

    // Perform jump search
    int result = jumpSearch(array, size, target);

    // Display the result
    if (result != -1) {
        printf("Element %d found at index %d.\n", target, result);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    return 0;
}
