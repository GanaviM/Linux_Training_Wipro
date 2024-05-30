#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_NAME "/dev/user_space_dev" // Replace with your actual device name

int main() {
  int fd;
  char buffer[50];

  // Open the device file
  fd = open(DEVICE_NAME, O_RDWR);
  if (fd == -1) {
    perror("open");
    return 1;
  }

  // Read data from the device
  ssize_t read_size = read(fd, buffer, sizeof(buffer));
  if (read_size < 0) {
    perror("read");
    close(fd);
    return 1;
  }

  printf("Read from device: %s\n", buffer);

  // Write data to the device
  const char *data_to_write = "Data from user space";
  ssize_t write_size = write(fd, data_to_write, strlen(data_to_write));
  if (write_size < 0) {
    perror("write");
    close(fd);
    return 1;
  }

  printf("Successfully wrote %zd bytes to device\n", write_size);

  close(fd);
  return 0;
}
