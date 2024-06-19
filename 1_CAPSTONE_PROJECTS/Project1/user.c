#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEVICE_FILE_NAME "/dev/simchardev"
#define BUF_LEN 80

// IOCTL Commands
#define IOCTL_SET_MSG _IOW('a', 1, char *)
#define IOCTL_GET_MSG _IOR('a', 2, char *)

void set_message(int file_desc, char *message) {
    int ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);
    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
}

void get_message(int file_desc) {
    char message[BUF_LEN];
    int ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);
    if (ret_val < 0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    printf("The message is: %s\n", message);
}

int main() {
    int file_desc;
    char read_buffer[BUF_LEN];
    int read_bytes;

    // Open the device file
    file_desc = open(DEVICE_FILE_NAME, O_RDWR);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }

    // Set a message using ioctl
    set_message(file_desc, "Hello from user program!");

    // Read message from the device
    read_bytes = read(file_desc, read_buffer, BUF_LEN);
    if (read_bytes < 0) {
        printf("Failed to read from device\n");
        close(file_desc);
        exit(-1);
    }
    read_buffer[read_bytes] = '\0';  // Null-terminate the string
    printf("Read from device: %s\n", read_buffer);

    // Get the message using ioctl
    get_message(file_desc);

    // Close the device file
    close(file_desc);

    return 0;
}
