#include "heap_sort.h"

// Function to heapify a subtree rooted with node i
void heapify(int array[], int size, int index) {
    int largest = index; // Initialize largest as root
    int left = 2 * index + 1; // Left child index
    int right = 2 * index + 2; // Right child index

    // If left child is larger than root
    if (left < size && array[left] > array[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < size && array[right] > array[largest])
        largest = right;

    // If largest is not root
    if (largest != index) {
        // Swap array[index] and array[largest]
        int temp = array[index];
        array[index] = array[largest];
        array[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(array, size, largest);
    }
}

// Function to perform heap sort
void heapSort(int array[], int size) {
    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    // Extract elements from heap one by one
    for (int i = size - 1; i > 0; i--) {
        // Move current root to end
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // Call heapify on the reduced heap
        heapify(array, i, 0);
    }
}

