#include "binary_search.h"

// Function to perform binary search
int binarySearch(const int array[], int size, int target) {
    int left = 0; // Left index of the search range
    int right = size - 1; // Right index of the search range

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate the middle index

        if (array[mid] == target) { // If target found at mid
            return mid; // Return the index of the target
        }
        if (array[mid] < target) { // If target is greater, search in the right half
            left = mid + 1;
        } else { // If target is smaller, search in the left half
            right = mid - 1;
        }
    }
    return -1; // Return -1 if target not found in the array
}
