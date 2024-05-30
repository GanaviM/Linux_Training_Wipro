#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/add_buffer_device"
#define MEMORY_SIZE 4096  // 4KB

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    int num1, num2;
    char operation;
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operation (+ or -): ");
    scanf(" %c", &operation);

    char buffer[sizeof(int) * 2 + sizeof(char)];
    memcpy(buffer, &num1, sizeof(int));
    memcpy(buffer + sizeof(int), &num2, sizeof(int));
    memcpy(buffer + sizeof(int) * 2, &operation, sizeof(char));

    if (write(fd, buffer, sizeof(buffer)) < 0) {
        perror("write");
        close(fd);
        return -1;
    }

    int result;
    if (read(fd, &result, sizeof(result)) < 0) {
        perror("read");
        close(fd);
        return -1;
    }

    printf("Calculation result: %d\n", result);

    close(fd);
    return 0;
}
