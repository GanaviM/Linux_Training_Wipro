#include <stdio.h>       // Standard Input/Output header
#include <fcntl.h>       // File control options header
#include <unistd.h>      // Standard symbolic constants and types header
#include <sys/ioctl.h>   // Input/Output control header

#define LED_DEV "/dev/led_dev"  // Define the device file path

int main(int argc, char *argv[]) {   // Main function starts, argc is the argument count, argv is the argument vector
    int fd, ret;                     // Declare file descriptor and return value variables
    char value;                      // Declare a variable to hold the value to write to the device

    // Check if the number of arguments is not equal to 2 or if the argument is not '0' or '1'
    if (argc != 2 || (argv[1][0] != '0' && argv[1][0] != '1')) {
        // Print usage message to stderr
        fprintf(stderr, "Usage: %s <0|1>\n", argv[0]);
        return 1;                    // Return with an error code
    }

    // Open the device file with write-only access
    fd = open(LED_DEV, O_WRONLY);
    if (fd < 0) {                    // Check if the file descriptor is invalid
        perror("open");              // Print the error message for open failure
        return 1;                    // Return with an error code
    }

    value = argv[1][0];              // Set the value to be written to the device based on the command line argument

    // Write the value to the device file
    ret = write(fd, &value, sizeof(value));
    if (ret < 0) {                   // Check if the write operation failed
        perror("write");             // Print the error message for write failure
        close(fd);                   // Close the file descriptor
        return 1;                    // Return with an error code
    }

    close(fd);                       // Close the file descriptor
    return 0;                        // Return success
}
