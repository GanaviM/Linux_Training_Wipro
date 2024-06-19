#include <stdio.h>

int main() {
    int user_id = 1000000000;
    user_id++;
    if (user_id > 100) {
        printf("Access granted!\n");
    } else {
        printf("Access denied!\n");
    }
    return 0;
}
