#include <stdio.h>
#include <unistd.h>

void _start() {
    const char msg[] = "hello, world\n"; // Define a character array containing the message
    write(1, msg, sizeof(msg) - 1);      // Write the message to the standard output (file descriptor 1)
    _exit(0);                             // Exit the program with a status code of 0
}
