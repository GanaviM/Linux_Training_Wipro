#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE_PATH "/dev/block_ioctl_device"
#define IOCTL_MAGIC 'k'
#define IOCTL_CMD _IOW(IOCTL_MAGIC, 1, int)

int main() {
    int fd;
    int value = 42;
    int read_value;

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    printf("Writing value to device...\n");
    if (write(fd, &value, sizeof(value)) < 0) {
        perror("Failed to write to the device");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Reading value from device...\n");
    if (read(fd, &read_value, sizeof(read_value)) < 0) {
        perror("Failed to read from the device");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Read value: %d\n", read_value);

    close(fd);
    return EXIT_SUCCESS;
}
