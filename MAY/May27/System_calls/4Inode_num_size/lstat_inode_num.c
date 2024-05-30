#include <stdio.h>
#include <sys/stat.h>

int main() {
    char filename[100]; // To store filename
    struct stat file_stat; // To store file information

    // Prompt user to enter filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Use lstat() to retrieve file information
    if (lstat(filename, &file_stat) == -1) {
        printf("Error: Could not get file information.\n");
        return 1;
    }

    // Display file information
    printf("File: %s\n", filename);
    printf("Inode number: %ld\n", (long)file_stat.st_ino);
    printf("Block size: %ld bytes\n", (long)file_stat.st_blksize);

    return 0;
}
