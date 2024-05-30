#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_NAME "/dev/pthreads_double_integer"

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int value = 0;

void *increment_thread(void *arg) {
  int fd;

  fd = open(DEVICE_NAME, O_RDWR);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 400; i++) {
    //pthread_mutex_lock(&mutex);
    value++;
    // Simulate interaction with kernel module
    write(fd, &value, sizeof(int));
    //pthread_mutex_unlock(&mutex);
    usleep(1000); // Simulate some work
  }

  close(fd);
  return NULL;
}

int main(void) {
  pthread_t threads[2];

  // Create threads
  for (int i = 0; i < 2; i++) {
    if (pthread_create(&threads[i], NULL, increment_thread, NULL) != 0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  // Wait for threads to finish
  for (int i = 0; i < 2; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  printf("Final value: %d\n", value);

  //pthread_mutex_destroy(&mutex);
  return EXIT_SUCCESS;
}
