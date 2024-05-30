#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_NAME "/dev/reverse_string"
#define MAX_LENGTH 100

int main() {
    int fd;
    char input_string[MAX_LENGTH];
    char reversed_string[MAX_LENGTH];

    // Open the device file
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file");
        return 1;
    }

    printf("Enter a string to reverse: ");
    fgets(input_string, MAX_LENGTH, stdin);

    // Write the input string to the device
    write(fd, input_string, strlen(input_string));

    // Read the reversed string from the device
    read(fd, reversed_string, MAX_LENGTH);

    printf("Reversed string received from device: %s\n", reversed_string);

    // Close the device file
    close(fd);

    return 0;
}

