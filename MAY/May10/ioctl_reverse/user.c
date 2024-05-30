#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEVICE_FILE "/dev/reverse_ioctl_dev"
#define REVERSE_STRING _IOR('q', 1, char *)

int main() {
    int fd;
    char message[] = "Hello World!";
    int ret;

    // Open the device file
    fd = open(DEVICE_FILE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device file");
        return -1;
    }

    // Perform the ioctl operation to reverse the string
    ret = ioctl(fd, REVERSE_STRING, &message);
    if (ret < 0) {
        perror("IOCTL failed");
        close(fd);
        return -1;
    }

    // Display the reversed string
    printf("Reversed string: %s\n", message);

    // Close the device file
    close(fd);

    return 0;
}
