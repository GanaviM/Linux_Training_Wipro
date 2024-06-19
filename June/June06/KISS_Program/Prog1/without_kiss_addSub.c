#include <stdio.h>

int main() {
    int x = 10, y = 5;

    // Complex logic with unnecessary abstraction
    int sum = add(x, y); // Function call instead of simple addition
    printf("Sum: %d\n", sum);

    int diff = subtract(x, y); // Function call instead of simple subtraction
    printf("Difference: %d\n", diff);

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
