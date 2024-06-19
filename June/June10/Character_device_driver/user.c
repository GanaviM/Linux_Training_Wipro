#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE "/dev/temp_sensor"

int main() {
    int fd;
    char buf[4];
    int ret;

    fd = open(DEVICE, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open the device");
        return errno;
    }

    ret = read(fd, buf, sizeof(buf));
    if (ret < 0) {
        perror("Failed to read the temperature");
        close(fd);
        return errno;
    }

    printf("Temperature: %s\n", buf);

    close(fd);
    return 0;
}
