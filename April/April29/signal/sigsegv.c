#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler for SIGSEGV (segmentation fault)
void sigsegv_handler(int signum) {
    printf("Segmentation fault occurred. Exiting the program.\n");
    exit(EXIT_FAILURE);
}

int main() {
    // Register the signal handler for SIGSEGV
    signal(SIGSEGV, sigsegv_handler);

    // Access a null pointer to cause a segmentation fault
    int *ptr = NULL;
    *ptr = 10; // This will cause a segmentation fault

    // This line will not be reached if a segmentation fault occurs
    printf("This line will not be executed if a segmentation fault occurs.\n");

    return EXIT_SUCCESS;
}
