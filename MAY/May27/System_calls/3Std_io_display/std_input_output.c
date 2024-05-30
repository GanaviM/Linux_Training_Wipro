#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read from standard input and display on standard output
    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("Error writing to stdout");
            return 1;
        }
    }

    // Check for read error
    if (bytes_read == -1) {
        perror("Error reading from stdin");
        return 1;
    }

    return 0;
}
