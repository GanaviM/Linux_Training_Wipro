#include "bubble_sort.h"

// Function to perform bubble sort
void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // Last i elements are already in place, so we don't need to compare them
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Swap array[j] and array[j+1]
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
