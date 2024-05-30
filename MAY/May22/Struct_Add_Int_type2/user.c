#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/struct_addsub_integer"
#define MEMORY_SIZE 4096  // 4KB
#define MAX_NUMBERS 10

struct Calculation {
    int numbers[MAX_NUMBERS];
    char operations[MAX_NUMBERS - 1]; // '+' or '-'
    int count;
    int result;
};

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    struct Calculation calc;
    printf("Enter the number of integers (up to 10): ");
    scanf("%d", &calc.count);

    if (calc.count > MAX_NUMBERS) {
        printf("Error: Cannot enter more than 10 integers.\n");
        close(fd);
        return -1;
    }

    printf("Enter %d integers:\n", calc.count);
    for (int i = 0; i < calc.count; ++i) {
        printf("Enter the integer %d: ", i + 1);
        scanf("%d", &calc.numbers[i]);
    }

    for (int i = 0; i < calc.count - 1; ++i) {
        printf("Enter the operation after integer %d (+ or -): ", i + 1);
        scanf(" %c", &calc.operations[i]);
    }

    if (write(fd, &calc, sizeof(struct Calculation)) < 0) {
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

    memcpy(&calc, mapped_memory, sizeof(struct Calculation));

    printf("The calculation on %d integers: ", calc.count);
    for (int i = 0; i < calc.count; ++i) {
        if (i != 0) {
            printf(" %c ", calc.operations[i - 1]);
        }
        printf("%d", calc.numbers[i]);
    }
    printf("\nResult = %d\n", calc.result);

    if (munmap(mapped_memory, MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
