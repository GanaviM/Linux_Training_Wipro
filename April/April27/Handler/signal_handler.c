#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler functions
void sigint_handler(int signum) {
    printf("Caught SIGINT signal\n");
    // Perform cleanup actions here if needed
    exit(signum); // Terminate the program
}

void sigterm_handler(int signum) {
    printf("Caught SIGTERM signal\n");
    // Perform cleanup actions here if needed
    exit(signum); // Terminate the program
}

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV signal (Segmentation fault)\n");
    // Perform cleanup actions here if needed
    exit(signum); // Terminate the program
}

int main() {
    // Registering signal handlers for SIGINT, SIGTERM, and SIGSEGV
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGSEGV, sigsegv_handler);
    printf("Running... Press Ctrl+C to interrupt\n");
    // Accessing NULL pointer to cause segmentation fault (SIGSEGV)
    int *ptr = NULL;
    *ptr = 10;

    // This code will not be reached due to the segmentation fault
    printf("This line will not be executed\n");
    return 0;
}
