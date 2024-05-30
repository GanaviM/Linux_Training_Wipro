#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define DEVICE_NAME "/dev/interrupt_chardev"

int main() {
    int fd;
    char buffer[256];
    ssize_t bytes_read;

    // Open the device file
    fd = open(DEVICE_NAME, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Read from the device
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Failed to read from the device");
        close(fd);
        return EXIT_FAILURE;
    }

    // Null-terminate the read data
    buffer[bytes_read] = '\0';

    // Print the read data
    printf("Message from the kernel: %s\n", buffer);

    // Close the device file
    close(fd);

    return EXIT_SUCCESS;
}

