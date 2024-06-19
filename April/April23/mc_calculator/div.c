//header files
#include "div.h"
#include<stdio.h>

//declares function prototype
float division(float x, float y)
{
	//using if condition
	if(y != 0.0)  //if value of y is not zero condition becomes true
	{
		return x / y; // return division of two integer
	}
	else
	{
		printf("Error: Division by zero\n"); // condition is false returns error and zero value
		return 0.0;
	}
}
