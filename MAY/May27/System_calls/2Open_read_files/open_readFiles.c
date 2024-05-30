#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "Test_file.txt"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    // Open the file in read-only mode
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Read and display each line from the file
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("Error writing to stdout");
            close(fd);
            return 1;
        }
    }

    // Check for read error or end-of-file
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}
