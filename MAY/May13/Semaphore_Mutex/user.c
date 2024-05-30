#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#define DEVICE_NAME "/dev/semaphore_mutex"

int main() {
    int fd;
    int data = 10; // Sample data to send to kernel

    // Open the device file
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Send data to the kernel using ioctl (illustrative example)
    if (ioctl(fd, 0, &data) < 0) {
        perror("ioctl");
        exit(1);
    }

    // Simulate user-space work (replace with actual work)
    printf("User program doing some work...\n");
    sleep(2);

    // Close the device file
    close(fd);

    return 0;
}
