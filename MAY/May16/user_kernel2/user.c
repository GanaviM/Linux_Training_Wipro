#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEVICE_NAME "/dev/my_data_transfer"
#define DATA_SIZE sizeof(struct user_data)

struct user_data {
  int value;
  char message[20];
};

int main() {
  int fd, ret;
  struct user_data data;

  // Open the device
  fd = open(DEVICE_NAME, O_WRONLY);
  if (fd == -1) {
    perror("Failed to open device");
    exit(1);
  }

  // Prepare data to send
  data.value = 42;
  snprintf(data.message, sizeof(data.message), "Hello from user-space!");

  // Send data to the kernel
  ret = write(fd, &data, DATA_SIZE);
  if (ret != DATA_SIZE) {
    perror("Failed to write data");
    close(fd);
    exit(1);
  }

  printf("Data sent successfully!\n");

  // Close the device (optional, as the program exits)
  close(fd);

  return 0;
}
