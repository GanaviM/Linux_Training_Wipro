#include "quick_sort.h"

// Function to partition the array and return the partitioning index
int partition(int array[], int low, int high) {
    int pivot = array[high]; // Pivot element (last element)
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (array[j] < pivot) {
            i++; // Increment index of smaller element
            // Swap array[i] and array[j]
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // Swap array[i+1] and array[high] (or pivot)
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

// Function to perform quicksort
void quickSort(int array[], int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(array, low, high);

        // Recursively sort elements before and after partition
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

