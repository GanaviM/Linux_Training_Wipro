#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define NUM_THREADS 3

// Signal handler function for SIGUSR1
void sigusr1_handler(int signum) {
    printf("Thread ID: %ld received SIGUSR1 signal. Custom message: Hello from thread!\n", pthread_self());
}

// Thread function
void *thread_function(void *arg) {
    // Register signal handler for SIGUSR1
    signal(SIGUSR1, sigusr1_handler);

    // Print thread ID
    printf("Thread ID: %ld started.\n", pthread_self());

    // Infinite loop to keep the thread alive
    while (1) {
        sleep(1); // Sleep for 1 second
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Send SIGUSR1 signal to each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_kill(threads[i], SIGUSR1);
    }

    // Wait for threads to finish (will not reach here)
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
