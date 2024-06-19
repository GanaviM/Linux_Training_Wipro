#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler for SIGINT (Ctrl+C)
void sigint_handler(int signum) {
    printf("\nCtrl+C pressed. Exiting the program gracefully.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Register the signal handler
    signal(SIGINT, sigint_handler);

    printf("Press Ctrl+C to exit the program.\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do nothing, waiting for Ctrl+C
    }

    return EXIT_SUCCESS;
}
