#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEVICE_NAME "/dev/my_device"

int main(int argc, char *argv[]) {
  int fd;
  char buffer[100];

  // Open the device driver
  fd = open(DEVICE_NAME, O_RDWR);
  if (fd < 0) {
    perror("Failed to open device");
    return 1;
  }

  // Write data to the device
  if (write(fd, "Hello from user-space!", 22) < 0) {
    perror("Failed to write to device");
    close(fd);
    return 1;
  }

  // Read data from the device
  if (read(fd, buffer, sizeof(buffer)) < 0) {
    perror("Failed to read from device");
    close(fd);
    return 1;
  }

  printf("Read from device: %s\n", buffer);

  // Close the device
  close(fd);

  return 0;
}
