#include <stdio.h>
#include "linear_search.h"

int main() {
    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]); // Calculate the size of the array
    int target = 30; // Example target value to search

    // Perform linear search
    int result = linearSearch(array, size, target);

    // Display the result
    if (result != -1) {
        printf("Element %d found at index %d.\n", target, result);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    return 0;
}
