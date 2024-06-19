#include "linear_search.h"

// Function to perform linear search
int linearSearch(const int array[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) { // If target found at index i
            return i; // Return the index of the target
        }
    }
    return -1; // Return -1 if target not found in the array
}
