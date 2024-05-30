#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/char_dev"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    char write_buffer[BUFFER_SIZE] = "Hello, this is a test message!";
    char read_buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;

    // Open the device
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Write data to the device
    bytes_written = write(fd, write_buffer, strlen(write_buffer));
    if (bytes_written < 0) {
        perror("Failed to write to the device");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Wrote %zd bytes to the device: %s\n", bytes_written, write_buffer);

    // Close and reopen the device to reset the offset
    close(fd);
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to reopen the device");
        return EXIT_FAILURE;
    }

    // Read data from the device
    bytes_read = read(fd, read_buffer, BUFFER_SIZE);
    if (bytes_read < 0) {
        perror("Failed to read from the device");
        close(fd);
        return EXIT_FAILURE;
    }

    // Null-terminate the read buffer
    read_buffer[bytes_read] = '\0';

    printf("Read %zd bytes from the device: %s\n", bytes_read, read_buffer);

    // Close the device
    close(fd);

    return EXIT_SUCCESS;
}
