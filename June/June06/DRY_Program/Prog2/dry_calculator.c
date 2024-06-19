#include <stdio.h>

// Function prototypes
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
void print_result(const char* operation, int result);

int main() {
    int x = 10, y = 5;

    // Perform operations using helper functions
    print_result("Addition", add(x, y));
    print_result("Subtraction", subtract(x, y));
    print_result("Multiplication", multiply(x, y));
    print_result("Division", divide(x, y));

    return 0;
}

// Function to add two numbers
int add(int a, int b) {
    return a + b;
}

// Function to subtract two numbers
int subtract(int a, int b) {
    return a - b;
}

// Function to multiply two numbers
int multiply(int a, int b) {
    return a * b;
}

// Function to divide two numbers
int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero.\n");
        return 0;
    }
}

// Function to print the result of an operation
void print_result(const char* operation, int result) {
    printf("%s result: %d\n", operation, result);
}
