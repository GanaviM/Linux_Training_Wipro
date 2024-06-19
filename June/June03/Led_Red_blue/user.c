#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define LED_DEV "/dev/led_dev"

int main(int argc, char *argv[]) {
    int fd, ret;
    char value;

    if (argc != 2 || (argv[1][0] != '0' && argv[1][0] != '1')) {
        fprintf(stderr, "Usage: %s <0|1>\n", argv[0]);
        return 1;
    }

    value = argv[1][0] - '0'; // Convert '0'/'1' to integer 0/1

    // Open the device file
    fd = open(LED_DEV, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Write the value to the device
    ret = write(fd, &value, sizeof(value));
    if (ret < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("LED state set to %d\n", value);

    // Close the device file
    close(fd);
    return 0;
}
