#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_SIZE 1048576 // 1 MB
#define NUM_FILES 100
#define READ_WRITE_BUFFER_SIZE 4096

// Interface for file operations
typedef struct {
    void (*execute)(); // Function pointer for executing a file operation
} FileOperation;

// File creator function
void create_files() {
    for (int i = 0; i < NUM_FILES; i++) {
        char filename[20];
        sprintf(filename, "testfile_%d.txt", i);
        FILE *file = fopen(filename, "w"); // Open file for writing
        if (file == NULL) {
            perror("File creation failed"); // Print error message if file creation failed
            exit(EXIT_FAILURE); // Exit the program with failure status
        }
        fclose(file); // Close the file
    }
}

// File writer function
void write_files() {
    char buffer[READ_WRITE_BUFFER_SIZE];
    for (int i = 0; i < READ_WRITE_BUFFER_SIZE; i++) {
        buffer[i] = 'A' + (i % 26); // Fill buffer with characters from 'A' to 'Z'
    }

    for (int i = 0; i < NUM_FILES; i++) {
        char filename[20];
        sprintf(filename, "testfile_%d.txt", i);
        FILE *file = fopen(filename, "w"); // Open file for writing
        if (file == NULL) {
            perror("File open for writing failed"); // Print error message if file opening failed
            exit(EXIT_FAILURE); // Exit the program with failure status
        }
        for (int j = 0; j < FILE_SIZE / READ_WRITE_BUFFER_SIZE; j++) {
            fwrite(buffer, sizeof(char), READ_WRITE_BUFFER_SIZE, file); // Write buffer to file
        }
        fclose(file); // Close the file
    }
}

// File reader function
void read_files() {
    char buffer[READ_WRITE_BUFFER_SIZE];

    for (int i = 0; i < NUM_FILES; i++) {
        char filename[20];
        sprintf(filename, "testfile_%d.txt", i);
        FILE *file = fopen(filename, "r"); // Open file for reading
        if (file == NULL) {
            perror("File open for reading failed"); // Print error message if file opening failed
            exit(EXIT_FAILURE); // Exit the program with failure status
        }
        while (fread(buffer, sizeof(char), READ_WRITE_BUFFER_SIZE, file) == READ_WRITE_BUFFER_SIZE);
        fclose(file); // Close the file
    }
}

// File deleter function
void delete_files() {
    for (int i = 0; i < NUM_FILES; i++) {
        char filename[20];
        sprintf(filename, "testfile_%d.txt", i);
        if (remove(filename) != 0) {
            perror("File deletion failed"); // Print error message if file deletion failed
            exit(EXIT_FAILURE); // Exit the program with failure status
        }
    }
}

// Function to measure elapsed time
double measure_time(FileOperation operation, const char *description) {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Record the starting time
    
    // Execute the specified file operation
    operation.execute();
    
    end = clock(); // Record the ending time

    // Calculate CPU time used
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // Print the elapsed time
    printf("%s: %f seconds\n", description, cpu_time_used);
    
    return cpu_time_used;
}

int main() {
    // Define file operation objects
    FileOperation create_operation = {.execute = create_files};
    FileOperation write_operation = {.execute = write_files};
    FileOperation read_operation = {.execute = read_files};
    FileOperation delete_operation = {.execute = delete_files};

    // Measure time for file creation
    measure_time(create_operation, "File creation");

    // Measure time for writing to files
    measure_time(write_operation, "File writing");

    // Measure time for reading from files
    measure_time(read_operation, "File reading");

    // Measure time for file deletion
    measure_time(delete_operation, "File deletion");

    return 0;
}
