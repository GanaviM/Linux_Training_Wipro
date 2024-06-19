#include <stdio.h>
#include <time.h>

int main() {
    // Start the clock
    clock_t start = clock();

    // Original Loop for Palindrome Check
    int num = 12321; // Check if 12321 is a palindrome
    int reversed = 0, original = num;
    while (num > 0) {
        reversed = (reversed * 10) + (num % 10);
        num /= 10;
    }
    int is_palindrome_original = (original == reversed);

    // Stop the clock
    clock_t end = clock();

    // Calculate the elapsed time
    double time_taken_original = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%d %s a palindrome (Original Loop).\n", original, is_palindrome_original ? "is" : "is not");
    printf("Time taken for palindrome check (Original Loop): %f seconds\n", time_taken_original);

    return 0;
}
