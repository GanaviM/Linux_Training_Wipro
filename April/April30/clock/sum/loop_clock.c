#include <stdio.h>
#include <time.h>
 
int main() {
    // Start the clock
    clock_t start = clock();
 
    // Original Loop (Less efficient)
    int sum = 0;
    int n = 1000;
    for (int i = 0; i < n; i++) {
        sum += i;
    }
 
    // Stop the clock
    clock_t end = clock();
 
    // Calculate the elapsed time
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
 
    printf("Sum: %d\n", sum);
    printf("Time taken for the original loop: %f seconds\n", time_taken);
 
    return 0;
}
