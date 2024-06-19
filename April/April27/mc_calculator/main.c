//Using headerfiles
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

//Main function
int main() {
    // Declaring the variable of integer type
    int choice;
    int num1, num2, num3, num4, result;

   //Printing the options and inputs 
    printf("1: Addition\n2: Subtraction\n3: Multiplication\n4: Division\n5: Quit\n");
    printf("Enter the option:\n");

    //Choosing the options using while loop
    while (1) {
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting program.\n");
            break;
        }

	//using the switch statment for 
        switch (choice) {
            case 1: //Addition of 3 numbers
		printf("Enter 3 numbers for adding: \n");
                scanf("%d %d %d", &num1, &num2, &num3);
                result = add(num1, num2, num3);
                printf("Sum of %d, %d, and %d is %d\n", num1, num2, num3, result);
		printf("\n\nEnter 1 - 4 for other options or 5 for quiting\n");
                break;
            case 2: //Subtraction of 4 numbers
		printf("Enter 4 numbers for subtracting:\n");
                scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
                result = sub(num1, num2, num3, num4);
                printf("Difference of %d, %d, %d, and %d is %d\n", num1, num2, num3, num4, result);
                printf("\n\nEnter 1 - 4 for other options or 5 for quiting\n");
		break;
            case 3:// Multiplication of three numbers
		printf("Enter 3  numbers for multiplication:\n");
                scanf("%d %d %d", &num1, &num2, &num3);
                result = mul(num1, num2, num3);
                printf("Product of %d, %d, and %d is %d\n", num1, num2, num3, result);
                printf("\n\nEnter 1 - 4 for other options or 5 for quiting\n");
		break;
            case 4: //Division of two numbers
		float num5, num6, result1;//declaring variables of floating type
		printf("Enter 2 numbers for division:\n");
                scanf("%f %f", &num5, &num6);
                result1 = division(num5, num6);
		printf("Division of %f and %f is %f\n", num5, num6, result1);
		printf("\n\nEnter 1 - 4 for other options or 5 for quiting\n");
                break;
            default:// default works if cases are not between 1-4 and ask for exit
                printf("Invalid choice\n");
		printf("Enter 5 to quit\n");
        }
    }

    return 0;
}
