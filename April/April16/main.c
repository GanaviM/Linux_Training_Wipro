#include<stdio.h>
#include "add.h"

int main()
{
	int a = 5, b = 7;
	int sum = add(a, b);
	printf("sum: %d\n", sum);
	return 0;
}
