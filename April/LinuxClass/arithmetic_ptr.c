#include <stdio.h>

int main()
{
	int arr[] = {10, 20, 30, 40, 50};
	int *ptr = arr;

	printf("Element at position 1: %d\n", *ptr);
	printf("Element at position 2: %d\n", *(ptr + 1));
	printf("Element at position 3: %d\n", *(ptr + 2));
	printf("Element at position 4: %d\n", *(ptr + 3));
	printf("Element at position 5: %d\n", *(ptr + 4));

	return 0;
}

