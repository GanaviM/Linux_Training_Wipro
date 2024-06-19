#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Global variables to store the two numbers
int num1 = 0;
int num2 = 0;

int main() {
    // Ignore SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z)
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    printf("Press Ctrl+C to add two numbers and Ctrl+Z to subtract two numbers.\n");

    // Infinite loop to keep the program running
    while (1) {
        // Prompt the user to enter two numbers
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

        // Add the numbers and print the result
        printf("Sum: %d\n", num1 + num2);

        // Prompt the user to enter two numbers
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);

        // Subtract the numbers and print the result
        printf("Difference: %d\n", num1 - num2);
    }

    return EXIT_SUCCESS;
}
