#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/mmapping_device"
#define MEMORY_SIZE 4096  // 4KB

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    void *mapped_memory = mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }

    // Example: Writing to the mapped memory
    strcpy((char *)mapped_memory, "Hello from user space!");

    // Example: Reading from the mapped memory
    printf("Read from device: %s\n", (char *)mapped_memory);

    if (munmap(mapped_memory, MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
