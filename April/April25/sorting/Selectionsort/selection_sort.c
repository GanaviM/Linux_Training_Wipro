#include "selection_sort.h"

// Function to perform selection sort
void selectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i; // Assume the current element is the minimum

        // Find the index of the minimum element in the unsorted part of the array
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }

        // Swap the minimum element with the first element of the unsorted part
        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}
