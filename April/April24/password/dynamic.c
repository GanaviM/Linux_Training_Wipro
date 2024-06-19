#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr = (int*)malloc(sizeof(int));
    free(ptr);
    *ptr = 42;
    printf("Value: %d\n", *ptr);
    return 0;
}
