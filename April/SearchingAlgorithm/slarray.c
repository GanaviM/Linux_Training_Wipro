#include <stdio.h>

// Function to find the largest element in an integer array
int findLargest(int arr[], int n) {
    int largest = arr[0]; // Assume the first element is the largest

    // Iterate through the array to find the largest element
    for (int i = 1; i < n; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }

    return largest;
}

// Function to find the smallest element in an integer array
int findSmallest(int arr[], int n) {
    int smallest = arr[0]; // Assume the first element is the smallest

    // Iterate through the array to find the smallest element
    for (int i = 1; i < n; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }

    return smallest;
}

int main() {
    int arr[] = { 12, 45, 23, 6, 78, 53 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // Find the largest and smallest elements in the array
    int largest = findLargest(arr, n);
    int smallest = findSmallest(arr, n);

    printf("Largest element in the array: %d\n", largest);
    printf("Smallest element in the array: %d\n", smallest);

return 0;
}
