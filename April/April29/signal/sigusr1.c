#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGUSR1
void sigusr1_handler(int signum) {
    printf("Received SIGUSR1 signal.\n");
}

int main() {
    // Register the signal handler for SIGUSR1
    signal(SIGUSR1, sigusr1_handler);
    printf("Program started. Press Ctrl+C to exit.\n");

    //Starts while loop
    while (1) {
        // Generate the SIGUSR1 signal every 3 seconds
        sleep(3);
        kill(getpid(), SIGUSR1);
    }

    return EXIT_SUCCESS;
}
