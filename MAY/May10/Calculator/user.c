#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_NAME "/dev/cal_dev_drive"

int main() {
    int fd;
    char operation;
    int operand1, operand2;
    char buffer[100];
    int nbytes;

    // Open the device file
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file");
        return 1;
    }

    // Prompt the user for input
    printf("Enter the operation (+, -, *, /): ");
    scanf(" %c", &operation);
    printf("Enter operand 1: ");
    scanf("%d", &operand1);
    printf("Enter operand 2: ");
    scanf("%d", &operand2);

    // Write the operation and operands to the device
    sprintf(buffer, "%c %d %d", operation, operand1, operand2);
    nbytes = write(fd, buffer, strlen(buffer));
    if (nbytes < 0) {
        perror("Failed to write to device");
        close(fd);
        return 1;
    }

    // Read the result from the device
    printf("Result: ");
    nbytes = read(fd, buffer, sizeof(buffer));
    if (nbytes < 0) {
        perror("Failed to read from device");
        close(fd);
        return 1;
    }

    // Print the result
    printf("%s", buffer);

    // Close the device file
    close(fd);

    return 0;
}
