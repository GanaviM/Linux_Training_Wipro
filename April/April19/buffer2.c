#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int items = 0;
pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

void *producer(void *arg) {
    int item;
    while (1) {
        // Generate a random item
        item = rand() % 100;
        // Lock the mutex before accessing shared variables
        pthread_mutex_lock(&mutex);
        // Wait if the buffer is full
        while (items == BUFFER_SIZE) {
            printf("Producer waiting (buffer full)\n");
            pthread_cond_wait(&empty, &mutex);
        }
        // Add the item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        items++;
        printf("Producer produced: %d\n", item);
        // Signal the consumer that an item is now available
        pthread_cond_signal(&full);
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    while (1) {
        // Lock the mutex before accessing shared variables
        pthread_mutex_lock(&mutex);
        // Wait if the buffer is empty
        while (items == 0) {
            printf("Consumer waiting (buffer empty)\n");
            pthread_cond_wait(&full, &mutex);
        }
        // Remove the item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        items--;
        printf("Consumer consumed: %d\n", item);
        // Signal the producer that space is now available
        pthread_cond_signal(&empty);
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        // Simulate some processing on the consumed item
        sleep(1); // Replace with your actual consumption logic
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int num_producers = 2;
    int num_consumers = 3;
    srand(time(NULL)); // Seed the random number generator
    
    // Initialize mutex, condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    
    pthread_t producers[num_producers], consumers[num_consumers];
    
    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    
    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }
    
    // Join with all threads
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    
    return 0;
}
