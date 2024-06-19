#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Global variables to store the two numbers
int num1 = 0;
int num2 = 0;

// Signal handler for SIGINT (Ctrl+C)
void sigint_handler(int signum) {
    printf("Enter two numbers to add: ");
    scanf("%d %d", &num1, &num2);
    printf("Sum: %d\n", num1 + num2);
    exit(EXIT_SUCCESS); // Exit after addition
}

// Signal handler for SIGTSTP (Ctrl+Z)
void sigtstp_handler(int signum) {
    printf("Enter two numbers to subtract: ");
    scanf("%d %d", &num1, &num2);
    printf("Difference: %d\n", num1 - num2);
    exit(EXIT_SUCCESS); // Exit after subtraction
}

int main() {
    // Register the signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    printf("Press Ctrl+C to add two numbers and Ctrl+Z to subtract two numbers.\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do nothing, waiting for signals
    }

    return EXIT_SUCCESS;
}
