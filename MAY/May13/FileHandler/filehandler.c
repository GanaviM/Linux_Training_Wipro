#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

void handle_event(int fd, int watch_fd) {
    char buffer[BUF_LEN];
    ssize_t len;
    struct inotify_event *event;

    len = read(fd, buffer, BUF_LEN);
    if (len == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    event = (struct inotify_event *)buffer;
    while ((char *)event < buffer + len) {
        if (event->wd == watch_fd) {
            if (event->mask & IN_MODIFY) {
                printf("File modified: %s\n", event->name);
            }
            if (event->mask & IN_DELETE) {
                printf("File deleted: %s\n", event->name);
            }
            if (event->mask & IN_CREATE) {
                printf("File created: %s\n", event->name);
            }
            // Add more conditions for other event types if needed
        }
        event = (struct inotify_event *)((char *)event + EVENT_SIZE + event->len);
    }
}

int main(int argc, char *argv[]) {
    int fd, watch_fd;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = inotify_init();
    if (fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    // Watch for file/directory changes in the specified path
    watch_fd = inotify_add_watch(fd, argv[1], IN_MODIFY | IN_CREATE | IN_DELETE);
    if (watch_fd == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    printf("Watching directory: %s\n", argv[1]);

    while (1) {
        handle_event(fd, watch_fd);
    }

    // Close the inotify file descriptor
    close(fd);
    return 0;
}

