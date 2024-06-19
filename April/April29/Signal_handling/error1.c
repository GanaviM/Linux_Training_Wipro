#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Common signal handler function
void signal_handler(int signum) {
    if (signum == SIGINT) {
        printf("Caught SIGINT: Interrupt signal\n");
        // Handle SIGINT, such as cleanup or graceful shutdown
    } else if (signum == SIGTERM) {
        printf("Caught SIGTERM: Termination signal\n");
        // Handle SIGTERM, such as cleanup or graceful shutdown
    }
}

int main() {
    // Register the signal handler for SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("Unable to set up SIGINT signal handler");
        exit(EXIT_FAILURE);
    }

    // Register the signal handler for SIGTERM
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("Unable to set up SIGTERM signal handler");
        exit(EXIT_FAILURE);
    }

    // Main application code...
    printf("Waiting for signals...\n");

   // Infinite loop to keep the program running
    while (1) {
        // Do something...
    }

     return 0;
}
