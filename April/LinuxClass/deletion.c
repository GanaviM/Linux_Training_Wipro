#include <stdio.h>

int main()
{
	int arr[5];
	int i, indexToDelete = 0, numElements = 3;

	printf("Enter 3 elements: \n");
	for(i = 0; i < numElements; i++)
	{
		scanf("%d", &arr[i]);
	}
	

	for (i = indexToDelete; i < numElements - 1; i++)
	{
		arr[ i ] = arr[ i + 1 ];
	}

	numElements--;

	printf("Array after deletion element at index 0: \n");
	for(i = 0; i < numElements; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");

	return 0;
}
