#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/add_integer_dev2"
#define MEMORY_SIZE 4096  // 4KB

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    int num_count;
    printf("Enter the number of integers to be printed: ");
    scanf("%d", &num_count);

    if (num_count > 10) {
        printf("Error: Cannot enter more than 10 integers.\n");
        close(fd);
        return -1;
    }

    int numbers[num_count];
    char buffer[MEMORY_SIZE];
    char *buffer_ptr = buffer;

    printf("Enter %d integers:\n", num_count);
    for (int i = 0; i < num_count; ++i) {
        printf("Enter the integer %d: ", i + 1);
        scanf("%d", &numbers[i]);
        memcpy(buffer_ptr, &numbers[i], sizeof(int));
        buffer_ptr += sizeof(int);
    }

    if (write(fd, buffer, sizeof(int) * num_count) < 0) {
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

    printf("The integers entered are: ");
    for (int i = 0; i < num_count; ++i) {
        if (i != 0) printf(" + ");
        printf("%d", numbers[i]);
    }
    printf("\nResult = %d\n", result);

    if (munmap(mapped_memory, MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
