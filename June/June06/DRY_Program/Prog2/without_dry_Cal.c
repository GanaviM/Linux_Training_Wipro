#include <stdio.h>

int main() {
    int x = 10, y = 5;

    // Addition
    int sum = x + y;
    printf("Addition result: %d\n", sum);

    // Subtraction
    int difference = x - y;
    printf("Subtraction result: %d\n", difference);

    // Multiplication
    int product = x * y;
    printf("Multiplication result: %d\n", product);

    // Division
    if (y != 0) {
        int quotient = x / y;
        printf("Division result: %d\n", quotient);
    } else {
        printf("Error: Division by zero.\n");
    }

    return 0;
}
