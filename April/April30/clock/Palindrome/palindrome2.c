#include <stdio.h>
#include <time.h>

int main() {
    // Start the clock
    clock_t start = clock();

    // Unrolled Loop for Palindrome Check
    int num = 12321; // Check if 12321 is a palindrome
    int reversed = 0, original = num;
    while (num > 0) {
        reversed = (reversed * 10) + (num % 10);
        num /= 10;
        if (num > 0) {
            reversed = (reversed * 10) + (num % 10);
            num /= 10;
        }
    }
    int is_palindrome_unrolled = (original == reversed);

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_unrolled = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%d %s a palindrome (Unrolled Loop).\n", original, is_palindrome_unrolled ? "is" : "is not");
    printf("Time taken for palindrome check (Unrolled Loop): %f seconds\n", time_taken_unrolled);

    return 0;
}
