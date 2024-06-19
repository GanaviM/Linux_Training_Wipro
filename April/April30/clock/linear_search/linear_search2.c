#include <stdio.h>
#include <time.h>

int linear_search(int arr[], int n, int key) {
    for (int i = 0; i < n; i += 2) {
        if (arr[i] == key) {
            return i; // Return index of key if found
        }
        if (i + 1 < n && arr[i + 1] == key) {
            return i + 1; // Return index of key if found
        }
    }
    return -1; // Return -1 if key not found
}

int main() {
    // Start the clock
    clock_t start = clock();

    // Unrolled Loop for Linear Search
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 10;
    int result = linear_search(arr, n, key);

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_unrolled = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (result != -1) {
        printf("Element %d found at index %d (Unrolled Loop).\n", key, result);
    } else {
        printf("Element %d not found (Unrolled Loop).\n", key);
    }
    printf("Time taken for linear search (Unrolled Loop): %f seconds\n", time_taken_unrolled);

    return 0;
}
