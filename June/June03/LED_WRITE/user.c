#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h> // Include for string operations

#define LED_DEV "/dev/my_led_dev" // Updated device name

int main(int argc, char *argv[]) {
    int fd, ret;
    char value;
    char current_state;

    if (argc != 2 || (strcmp(argv[1], "on") != 0 && strcmp(argv[1], "off") != 0)) {
        fprintf(stderr, "Usage: %s <on|off>\n", argv[0]);
        return 1;
    }

    // Open the device file
    fd = open(LED_DEV, O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Perform read to get current LED state
    ret = read(fd, &current_state, sizeof(current_state));
    if (ret < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    if (strcmp(argv[1], "on") == 0 && current_state == '1') {
        printf("LED is already on\n");
    } else if (strcmp(argv[1], "off") == 0 && current_state == '0') {
        printf("LED is already off\n");
    } else {
        // Convert user input to character '0' or '1'
        value = (strcmp(argv[1], "on") == 0) ? '1' : '0';

        // Write the value to the device
        ret = write(fd, &value, sizeof(value));
        if (ret < 0) {
            perror("write");
            close(fd);
            return 1;
        }

        printf("LED state set to %c\n", value);
    }

    // Close the device file
    close(fd);
    return 0;
}
