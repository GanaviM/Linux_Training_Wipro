#include <stdio.h>

int factorial(int n) {

    if (n == 0) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    int num;
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &num);
    if (num < 0) {
        printf("Invalid.\n");
    }
    else {
        int fact = factorial(num);
        printf("Factorial of %d is: %d\n", num, fact);
    }
    return 0;
}
