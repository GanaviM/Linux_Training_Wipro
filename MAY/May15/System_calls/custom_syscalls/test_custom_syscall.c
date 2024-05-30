// test_custom_syscall.c

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_custom_syscall 333 // Match the number in syscall table

int main() {
    long int ret = syscall(__NR_custom_syscall);
    if (ret == 0) {
        printf("Custom syscall executed successfully.\n");
    } else {
        printf("Custom syscall failed.\n");
    }
    return 0;
}
