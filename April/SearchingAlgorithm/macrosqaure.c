#include<stdio.h>
#define SQUARE(x) ((x) * (x))


int main()
{
	int num1 = 5, num2 = 10;
	printf("Square of %d is :%d\n", num1, SQUARE(num1));
	printf("Square of %d is :%d\n", num2, SQUARE(num2));
	return 0;
}
