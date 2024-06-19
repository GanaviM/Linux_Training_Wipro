#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int signum) {
    printf("Caught SIGUSR1: User-defined signal received\n");
    // Perform any necessary actions in response to the signal
}

int main() {
    // Register the signal handler
    if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
        perror("Unable to set up signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Process ID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do nothing, waiting for SIGUSR1
        sleep(1);
    }

    return EXIT_SUCCESS;
}
