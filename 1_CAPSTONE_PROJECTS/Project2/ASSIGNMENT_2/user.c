#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/kernel.h>

#define SYS_LOG_MESSAGE 548  // Replace with the actual syscall number

// Function to send a message to the kernel log
int log_message(const char *message) {
    return syscall(SYS_LOG_MESSAGE, message);
}

// Function to handle the result of the system call
void handle_syscall_result(int result) {
    if (result == 0) {
        printf("Message sent successfully\n");
    } else {
        printf("Failed to send message: %d\n", result);
    }
}

int main() {
    const char *message = "Hello, Kernel!";  // Message to send to the kernel log

    // Log the message to the kernel and handle the result
    int result = log_message(message);
    handle_syscall_result(result);
    
    return 0;  // Return success
}
