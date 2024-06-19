#include <stdio.h>
#include <time.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    // Start the clock
    clock_t start = clock();

    // Original Loop for Bubble Sort
    int arr[] = {64, 34, 25, 12, 22, 11, 90}; // Sort the array
    int n = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, n);

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_original = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array (Original Loop): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nTime taken for sorting (Original Loop): %f seconds\n", time_taken_original);

    return 0;
}
