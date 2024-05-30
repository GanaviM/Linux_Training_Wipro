#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/simple_char_device"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    char write_buffer[BUFFER_SIZE] = "Hello from user space!";
    char read_buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;

    // Open the device file
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Write to the device
    bytes_written = write(fd, write_buffer, sizeof(write_buffer));
    if (bytes_written < 0) {
        perror("Failed to write to the device");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Wrote %zd bytes to the device: %s\n", bytes_written, write_buffer);

    // Seek to the beginning of the device
    lseek(fd, 0, SEEK_SET);

    // Read from the device
    bytes_read = read(fd, read_buffer, sizeof(read_buffer));
    if (bytes_read < 0) {
        perror("Failed to read from the device");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Read %zd bytes from the device: %s\n", bytes_read, read_buffer);

    // Close the device
    close(fd);
    return EXIT_SUCCESS;
}
