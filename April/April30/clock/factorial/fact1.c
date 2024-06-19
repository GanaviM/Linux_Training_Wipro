#include <stdio.h>
#include <time.h>

int main() {
    // Start the clock
    clock_t start = clock();

    // Original Loop for Factorial Calculation
    int n = 10; // Calculate factorial of 10
    int factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_original = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Factorial of %d (Original Loop): %d\n", n, factorial);
    printf("Time taken for factorial calculation (Original Loop): %f seconds\n", time_taken_original);

    return 0;
}
