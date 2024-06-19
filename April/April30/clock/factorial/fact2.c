#include <stdio.h>
#include <time.h>

int main() {
    // Start the clock
    clock_t start = clock();

    // Unrolled Loop for Factorial Calculation
    int n = 10; // Calculate factorial of 10
    int factorial = 1;
    for (int i = 1; i <= n; i += 2) {
        factorial *= i;
        if (i + 1 <= n) {
            factorial *= (i + 1);
        }
    }

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_unrolled = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Factorial of %d (Unrolled Loop): %d\n", n, factorial);
    printf("Time taken for factorial calculation (Unrolled Loop): %f seconds\n", time_taken_unrolled);

    return 0;
}
