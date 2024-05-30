#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define IOCTL_REVERSE_STRING _IOWR('q', 2, char *)

int main() {
    int fd;
    char message[100] = "Hello, world!";

    fd = open("/dev/IOCTL_string_reverse", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return -1;
    }

    // Call ioctl to reverse the string
    ioctl(fd, IOCTL_REVERSE_STRING, message);

    // Print the reversed string
    printf("Reversed string: %s\n", message);

    close(fd);
    return 0;
}
