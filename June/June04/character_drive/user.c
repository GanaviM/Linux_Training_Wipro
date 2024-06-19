#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/simple_char_dev"

int main() {
    int fd;
    char read_char;
    char write_char = 'A';

    // Open the device file
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return 1;
    }

    // Write a character to the device
    if (write(fd, &write_char, 1) < 0) {
        perror("Failed to write the character to the device");
        close(fd);
        return 1;
    }
    printf("Wrote character '%c' to the device\n", write_char);

    // Reset the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Read the character from the device
    if (read(fd, &read_char, 1) < 0) {
        perror("Failed to read the character from the device");
        close(fd);
        return 1;
    }
    printf("Read character '%c' from the device\n", read_char);

    // Close the device file
    close(fd);
    return 0;
}
