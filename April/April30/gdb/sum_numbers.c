#include <stdio.h>

int sum_of_natural_numbers(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

int main() {
    int n = 10;
    int result = sum_of_natural_numbers(n);
    printf("Sum of the first %d natural numbers is %d\n", n, result);
    return 0;
}
