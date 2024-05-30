#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/mmap_modify_device"
#define MEMORY_SIZE 4096  // 4KB

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    // Example: Writing to the device using write system call
    const char *write_msg = "Hello from user space!";
    ssize_t bytes_written = write(fd, write_msg, strlen(write_msg));
    if (bytes_written < 0) {
        perror("write");
        close(fd);
        return -1;
    }
    printf("Written to device: %s\n", write_msg);

    // Reset file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Example: Reading from the device using read system call
    char read_buffer[MEMORY_SIZE] = {0};
    ssize_t bytes_read = read(fd, read_buffer, sizeof(read_buffer) - 1);
    if (bytes_read < 0) {
        perror("read");
        close(fd);
        return -1;
    }
    printf("Read from device: %s\n", read_buffer);

    // Memory mapping the device
    void *mapped_memory = mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }

    // Example: Writing to the mapped memory
    strcpy((char *)mapped_memory, "Hello from user space via mmap!");

    // Example: Reading from the mapped memory
    printf("Read from device via mmap: %s\n", (char *)mapped_memory);

    if (munmap(mapped_memory, MEMORY_SIZE) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
