#include<stdio.h>
#include<stdlib.h>

int *allocateIntArray(int size)
{
	int *arr = (int *)malloc(size * sizeof(int));
	if (arr == NULL)
	{
		printf("Memory Allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	return arr;
}

int main()
{
	int size, i;
	int *array;

	printf("Enter the sixe of array: ");
	scanf("%d", &size);

	array = allocateIntArray(size);
	
	printf("Enter %d elements for the array: \n", size);
	for(i=0; i < size; i++)
	{
		scanf("%d", &array[i]);
	}

	printf("Elments of the array: \n");
	for(i = 0; i < size; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");

	free(array);
	return 0;
}
