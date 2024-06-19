#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE  5
pthread_mutex_t lock;
pthread_cond_t notFull, notEmpty;
int count;

void producer(char* buf) {
   for(;;) {
        pthread_mutex_lock(&lock);
        while(count == MAX_SIZE)
            pthread_cond_wait(&notFull, &lock); 
        buf[count] = getchar();
        count++;
        pthread_cond_signal(&notEmpty);
        pthread_mutex_unlock(&lock);
   }
}

void consumer(char* buf) {
   for(;;) {
        pthread_mutex_lock(&lock);
        while(count == 0)
            pthread_cond_wait(&notEmpty, &lock);
        putchar(buf[count-1]);
        count--;
        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&lock);
   }
}

int main() {
   char buffer[MAX_SIZE];
   pthread_t t1, t2; // Add consumer thread
   pthread_mutex_init(&lock, NULL);
   pthread_create(&t1, NULL, (void*)producer, &buffer);
   pthread_create(&t2, NULL, (void*)consumer, &buffer); // Create consumer thread
   pthread_join(t2, NULL); // Join consumer thread
   return 0;
}


