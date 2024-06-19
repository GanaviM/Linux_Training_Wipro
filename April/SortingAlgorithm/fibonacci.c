#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

void printFibonacci(int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", fibonacci(i));
    }
}

int main() {
    int n;
    printf("Enter the number of terms for Fibonacci series: ");
    scanf("%d", &n);
   
    printf("Fibonacci Series up to %d terms: ", n);
    printFibonacci(n);
   
    return 0;
}

