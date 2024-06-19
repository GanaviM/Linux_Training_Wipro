#include <stdio.h>

// Simple function to check if a number is even
int is_even(int number) {
    return number % 2 == 0;
}

int main() {
    int number = 4;
    if (is_even(number)) {
        printf("%d is even\n", number);
    } else {
        printf("%d is odd\n", number);
    }

    return 0;
}
