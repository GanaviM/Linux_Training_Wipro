#include <stdio.h>
#include "heap_sort.h"

int main() {
    int array[] = {312, 511, 313, 57, 26, 887}; // Example array to be sorted
    int size = sizeof(array) / sizeof(array[0]); // Calculate the size of the array

    // Display the original array
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Perform heap sort
    heapSort(array, size);

    // Display the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
