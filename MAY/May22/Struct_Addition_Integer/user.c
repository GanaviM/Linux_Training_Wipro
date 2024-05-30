#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_PATH "/dev/struct_add_device"
#define MEMORY_SIZE 4096  // 4KB
#define MAX_INTS 10

struct Numbers {
    int nums[MAX_INTS];
    int count;
    int sum;
};

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    struct Numbers nums;
    printf("Enter the number of integers to be printed (max %d): ", MAX_INTS);
    scanf("%d", &nums.count);

    if (nums.count > MAX_INTS || nums.count <= 0) {
        printf("Invalid number of integers.\n");
        close(fd);
        return -1;
    }

    printf("Enter %d integers:\n", nums.count);
    for (int i = 0; i < nums.count; ++i) {
        printf("Enter the integer %d: ", i + 1);
        scanf("%d", &nums.nums[i]);
    }

    if (write(fd, &nums, sizeof(struct Numbers)) < 0) {
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

    struct Numbers result;
    memcpy(&result, mapped_memory, sizeof(struct Numbers));

    printf("The integers entered are: ");
    for (int i = 0; i < result.count; ++i) {
        printf("%d", result.nums[i]);
        if (i != result.count - 1) {
            printf(" + ");
        }
    }
    printf("\nResult = %d\n", result.sum);

    if (munmap(mapped_memory, MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
