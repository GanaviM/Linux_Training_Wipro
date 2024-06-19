#include <stdio.h>
#include <time.h>
 
int main() {
    // Start the clock
    clock_t start = clock();
 
    // Unrolled Loop (improves performance for small Loop iterations)
    int sum = 0;
    int n = 1000;
    for (int i = 0; i < n; i += 2) {
        sum += i;
        if (i + 1 < n) {
            sum += i + 1;
        }
    }
 
    // Stop the clock
    clock_t end = clock();
 
    // Calculate the elapsed time
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
 
    printf("Sum: %d\n", sum);
    printf("Time taken for the unrolled loop: %f seconds\n", time_taken);
 
    return 0;
}
