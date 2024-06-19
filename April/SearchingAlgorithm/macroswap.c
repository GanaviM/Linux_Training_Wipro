#include<stdio.h>
#define SWAP(a,b) do { \
	(a)= (a) + (b);\
	(b) = (a) - (b);\
	(a) = (a) - (b);\
} while(0)

int main()
{
	int x = 5, y = 6;
	printf("Before swapping: x = %d, y = %d\n", x, y);
	SWAP(x, y);
	printf("After swapping: x = %d, y = %d\n", x, y);
	return 0;
}
