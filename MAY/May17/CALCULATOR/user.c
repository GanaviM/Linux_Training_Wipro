#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define DEVICE_PATH "/dev/calc_device"
#define IOCTL_MAGIC 'c'
#define IOCTL_CALC _IOWR(IOCTL_MAGIC, 1, calc_data_t)

typedef struct {
    int num1;
    int num2;
    char operation[8];
    int result;
    int error;
} calc_data_t;

void perform_calculation(int num1, int num2, const char *operation) {
    int fd;
    calc_data_t data;

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        exit(EXIT_FAILURE);
    }

    data.num1 = num1;
    data.num2 = num2;
    strncpy(data.operation, operation, sizeof(data.operation));

    if (ioctl(fd, IOCTL_CALC, &data) < 0) {
        perror("Failed to execute ioctl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (data.error) {
        printf("Error: Division by zero\n");
    } else {
        printf("Result of %s: %d\n", data.operation, data.result);
    }

    close(fd);
}

int main() {
    int num1, num2;
    char operation[8];

    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operation (+, -, *, /): ");
    scanf("%s", operation);

    perform_calculation(num1, num2, operation);

    return EXIT_SUCCESS;
}
