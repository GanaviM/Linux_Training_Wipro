#include <stdio.h>

void reverseArray(int arr[], int size) {
    int start = 0;      
    int end = size - 1; 
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

void printArray(int arr[], int size) {
    printf("Reversed array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter %d elements of the array: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    reverseArray(arr, size);

    printArray(arr, size);

    return 0;
}
