#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd;
    ssize_t ret;

    // Open the device file
    fd = open("/dev/my_tasklet_device", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    // Write to the device file
    ret = write(fd, "trigger", 7);
    if (ret < 0) {
        perror("Failed to write to the device");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Tasklet scheduled via device write\n");

    // Close the device file
    close(fd);

    return EXIT_SUCCESS;
}
