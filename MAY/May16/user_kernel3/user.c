#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define DEVICE_FILE "/dev/spinlock_dev"
#define DATA_SIZE sizeof(struct user_data)

struct user_data {
  int value;
  char message[20];
};

void *write_data(void *arg) {
  int fd = *((int *)arg);
  struct user_data data = {42, "Hello from user program"};

  if (write(fd, &data, sizeof(data)) < 0) {
    perror("Write failed");
    return NULL;
  }

  return NULL;
}

int main() {
  int fd;
  pthread_t thread_id;
  struct user_data read_data;

  fd = open(DEVICE_FILE, O_RDWR);
  if (fd < 0) {
    perror("Failed to open device file");
    return EXIT_FAILURE;
  }

  if (pthread_create(&thread_id, NULL, write_data, &fd) != 0) {
    perror("Thread creation failed");
    close(fd);
    return EXIT_FAILURE;
  }

  pthread_join(thread_id, NULL);

  if (read(fd, &read_data, sizeof(read_data)) < 0) {
    perror("Read failed");
    close(fd);
    return EXIT_FAILURE;
  }

  printf("Received data from kernel: value = %d, message = %s\n", read_data.value, read_data.message);

  close(fd);

  return EXIT_SUCCESS;
}
