#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SOURCE_FILENAME "hello.txt"
#define DESTINATION_FILENAME "copy_hello.txt"
#define BUFFER_SIZE 1024

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open the source file for reading
    source_fd = open(SOURCE_FILENAME, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing (create if it doesn't exist, truncate if it does)
    dest_fd = open(DESTINATION_FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    // Read from the source file and write to the destination file
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Close the source file
    if (close(source_fd) == -1) {
        perror("Error closing source file");
        close(dest_fd);
        return 1;
    }

    // Close the destination file
    if (close(dest_fd) == -1) {
        perror("Error closing destination file");
        return 1;
    }

    printf("File copied successfully.\n");
    return 0;
}
