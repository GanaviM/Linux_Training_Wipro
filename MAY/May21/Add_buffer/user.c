#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/add_buffer"
#define BUFFER_SIZE 128

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    char buffer[BUFFER_SIZE];

    // Get two numbers from the user
    int num1, num2;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Format the input numbers as a string and write it to the device
    sprintf(buffer, "%d %d", num1, num2);
    write(fd, buffer, sizeof(buffer));

    // Read the result from the device
    read(fd, buffer, sizeof(buffer));

    // Print the result
    printf("Result: %s\n", buffer);
    
    close(fd);
    return 0;
}

