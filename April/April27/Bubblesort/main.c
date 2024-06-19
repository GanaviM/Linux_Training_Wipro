#include <stdio.h>
#include "bubble_sort.h"

int main() {
    int array[] = {64, 134, 325, 142, 522, 611, 290}; // Example array to be sorted
    int size = sizeof(array) / sizeof(array[0]); // Calculate the size of the array

    // Display the original array
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Perform bubble sort
    bubbleSort(array, size);

    // Display the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
