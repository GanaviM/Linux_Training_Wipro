#include<stdio.h>
int divide(int a, int b)
{
	if(b == 0)
	{
		printf("Cannot be divided by zero\n");
		return 0;
	}
	return a / b;
}
