#include <stdio.h>

// function to check if a number is even
int is_even(int number) {
    if (number % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int number = 4;
    if (is_even(number) == 1) {
        printf("%d is even\n", number);
    } else {
        printf("%d is odd\n", number);
    }

    return 0;
}
