// user_program.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    off_t result = lseek(fd, 0, SEEK_END);
    if (result == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("File size: %lld bytes\n", (long long)result);

    close(fd);
    return 0;
}
