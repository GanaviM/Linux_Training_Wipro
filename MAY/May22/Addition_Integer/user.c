#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/integer_addition_device"
#define MEMORY_SIZE 4096  // 4KB

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    int nums[10];
    printf("Enter 10 integers in the format num1+num2+...+num10: ");
    for (int i = 0; i < 10; i++) {
        if (scanf("%d", &nums[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            close(fd);
            return -1;
        }
        if (i < 9) scanf("+"); // Ignore the '+' characters
    }

    char buffer[sizeof(int) * 10];
    memcpy(buffer, nums, sizeof(int) * 10);

    if (write(fd, buffer, sizeof(buffer)) < 0) {
        perror("write");
        close(fd);
        return -1;
    }

    void *mapped_memory = mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }

    int result;
    memcpy(&result, mapped_memory, sizeof(int));
    printf("The value of the calculation = %d\n", result);

    if (munmap(mapped_memory, MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
