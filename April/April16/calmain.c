#include<stdio.h>
#include "calculator.h"

int main()
{
	int num1, num2;
	char op;

	printf("Enter operator (+, -, *, /) : \n");
	scanf("%c", &op);

	printf("Enter two numbers: ");
	scanf("%d %d", &num1, &num2);

	switch(op){
		case '+' : 
			printf("%d + %d = %d", num1, num2, add(num1, num2));
			break;
		case '-' :
                        printf("%d - %d = %d", num1, num2, subtract(num1, num2));
                        break;
                case '*' :
                        printf("%d * %d = %d", num1, num2, multiply(num1, num2));
                        break;
		case '/' :
			if (num2 == 0)
				printf("Cannot be divided by zero.\n");
			else
				printf("%d / %d = %d\n", num1, num2, divide(num1, num2));
			break;
		default:
			printf("Invalid Operator\n");
	}
	return 0;
}

