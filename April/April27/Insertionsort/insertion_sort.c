#include "insertion_sort.h"

// Function to perform insertion sort
void insertionSort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i]; // Store the current element to be inserted
        int j = i - 1; // Index of the previous element

        // Move elements of array[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j]; // Move the element to the right
            j = j - 1; // Move to the previous element
        }
        array[j + 1] = key; // Insert the stored element at correct position
    }
}
