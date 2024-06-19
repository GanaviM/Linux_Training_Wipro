#include <stdio.h>

int main() {
    char username[10];
    printf("Enter username: ");
    gets(username);
    printf("Hello, %s!\n", username);
    return 0;
}
