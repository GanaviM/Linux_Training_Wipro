#include "jump_search.h"
#include <math.h>

// Function to perform jump search
int jumpSearch(const int array[], int size, int target) {
    int jump = (int)sqrt(size); // Calculate the jump size
    int left = 0; // Left index of the current block
    int right = jump; // Right index of the current block

    // Jump through the blocks until the target is found or the end of the array is reached
    while (right < size && array[right] < target) {
        left = right; // Move the left index to the start of the next block
        right += jump; // Move the right index to the end of the next block
    }

    // Perform linear search within the block
    for (int i = left; i <= fmin(right, size - 1); i++) {
        if (array[i] == target) { // If target found
            return i; // Return the index of the target
        }
    }

    return -1; // Return -1 if target not found in the array
}
