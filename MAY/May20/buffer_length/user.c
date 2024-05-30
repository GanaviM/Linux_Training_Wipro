#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>

#define DEVICE "/dev/example_char_device"
#define BUF_LEN 80

int main() {
    int fd = open(DEVICE, O_RDWR);
    if (fd == -1) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN | POLLOUT;

    char buffer[BUF_LEN];

    while (1) {
        int ret = poll(&pfd, 1, 5000); // 5-second timeout
        if (ret == -1) {
            perror("poll");
            close(fd);
            return EXIT_FAILURE;
        } else if (ret == 0) {
            printf("Timeout occurred! No data within 5 seconds.\n");
        } else {
            if (pfd.revents & POLLIN) {
                int bytes_read = read(fd, buffer, BUF_LEN);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    printf("Read data: %s\n", buffer);
                }
            }

            if (pfd.revents & POLLOUT) {
                char write_data[] = "Hello, device!";
                int bytes_written = write(fd, write_data, strlen(write_data));
                if (bytes_written > 0) {
                    printf("Written data: %s\n", write_data);
                }
            }
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}
