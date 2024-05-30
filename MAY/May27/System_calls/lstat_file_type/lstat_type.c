#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include <stdlib.h> for the realpath() function
#include <unistd.h> // Include <unistd.h> for the getcwd() function
#include <sys/stat.h>

// Function to extract file extension from filename
const char *get_file_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return ""; // No extension found
    }
    return dot + 1; // Return the extension (excluding the dot)
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    struct stat file_stat;

    // Check if the filename is not an absolute path
    if (filename[0] != '/') {
        // Get the current working directory
        char cwd[4096]; // Buffer to store the current working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("Error: Could not get current working directory");
            return 1;
        }
        
        // Concatenate the filename with the current working directory
        char *full_path = realpath(filename, NULL);
        if (full_path == NULL) {
            perror("Error: Could not get full path");
            return 1;
        }

        filename = full_path;
    }

    // Use lstat() to retrieve file information
    if (lstat(filename, &file_stat) == -1) {
        printf("Error: Could not get file information.\n");
        return 1;
    }

    // Check if the file is a directory
    if (S_ISDIR(file_stat.st_mode)) {
        printf("%s is a directory.\n", filename);
    } else if (S_ISREG(file_stat.st_mode)) {
        // If it's a regular file, determine the file type based on the file extension
        const char *extension = get_file_extension(filename);
        if (strcmp(extension, "txt") == 0) {
            printf("%s is a text file.\n", filename);
        } else if (strcmp(extension, "c") == 0) {
            printf("%s is a C source file.\n", filename);
        } else if (strcmp(extension, "py") == 0) {
            printf("%s is a Python script file.\n", filename);
        } else if (strcmp(extension, "ppt") == 0) {
            printf("%s is a PowerPoint presentation file.\n", filename);
        } else {
            printf("%s is a file with unknown extension.\n", filename);
        }
    } else {
        printf("%s is of unknown type.\n", filename);
    }

    return 0;
}
