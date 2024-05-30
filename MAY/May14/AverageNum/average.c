#include <stdio.h>

int main() {
    float num1, num2, average;

    // Prompt user for the first number
    printf("Enter the first number: ");
    scanf("%f", &num1);

    // Prompt user for the second number
    printf("Enter the second number: ");
    scanf("%f", &num2);

    // Calculate the average
    average = (num1 + num2) / 2;

    // Print the average
    printf("The average of %.2f and %.2f is %.2f\n", num1, num2, average);

    return 0;
}
