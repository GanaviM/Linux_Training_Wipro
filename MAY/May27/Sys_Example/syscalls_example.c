#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytes_written, bytes_read;
    char buffer[BUFFER_SIZE];

    // Open the file for writing (create if it doesn't exist, truncate if it does)
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Write some data to the file
    const char *data_to_write = "Hello, World!\nThis is a test file.\n";
    bytes_written = write(fd, data_to_write, strlen(data_to_write));
    if (bytes_written == -1) {
        perror("Failed to write to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Wrote %zd bytes to the file.\n", bytes_written);

    // Close the file
    if (close(fd) == -1) {
        perror("Failed to close the file after writing");
        exit(EXIT_FAILURE);
    }

    // Open the file for reading
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    // Read the data from the file
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Failed to read from file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the buffer to safely print it
    buffer[bytes_read] = '\0';

    printf("Read %zd bytes from the file:\n%s\n", bytes_read, buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Failed to close the file after reading");
        exit(EXIT_FAILURE);
    }

    return 0;
}
