#include <stdio.h>

int main()
{
	int arr[5];
	int i, num;

	printf("Enter 3 elements: \n");
	for(i = 0; i < 3; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Enter a number to insert: ");
	scanf("%d", &num);

	for (i = 2; i >= 0; i--)
	{
		arr[ i+1 ] = arr[ i ];
	}

	arr [1] = num;

	printf("Array after insertion: \n");
	for(i = 0; i < 5; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");

	return 0;
}

