#include <stdio.h>
#include "quick_sort.h"

int main() {
    int array[] = {10, 7, 8, 9, 1, 5}; // Example array to be sorted
    int size = sizeof(array) / sizeof(array[0]); // Calculate the size of the array

    // Display the original array
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Perform quicksort
    quickSort(array, 0, size - 1);

    // Display the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
