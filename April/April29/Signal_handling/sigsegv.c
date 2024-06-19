#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler for SIGSEGV
void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV: Segmentation fault\n");
    // Perform any necessary cleanup or actions
    exit(EXIT_FAILURE);
}

int main() {
    // Register the signal handler
    if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("Unable to set up signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Triggering a segmentation fault...\n");

    // Dereference a null pointer to trigger a segmentation fault
    int *ptr = NULL;
    *ptr = 42;

    // The following line should never be reached if SIGSEGV is properly handled
    printf("Segmentation fault not triggered!\n");

    return EXIT_SUCCESS;
}
