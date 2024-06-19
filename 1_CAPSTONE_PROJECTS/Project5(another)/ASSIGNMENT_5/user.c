#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// Constants
#define DEVICE_FILE_NAME "/dev/benchmarkdevice"
#define BUF_LEN 80

// Utility function for measuring execution time of a benchmark
void measure_time(void (*benchmark_func)(), const char *operation) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    benchmark_func();
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%s time: %f seconds\n", operation, cpu_time_used);
}

// File creation benchmark function
void benchmark_file_creation() {
    FILE *file = fopen("testfile.txt", "w");
    if (file) {
        fclose(file);
    }
}

// File deletion benchmark function
void benchmark_file_deletion() {
    remove("testfile.txt");
}

// File write benchmark function
void benchmark_file_write() {
    FILE *file = fopen("testfile.txt", "w");
    if (file) {
        char data[BUF_LEN] = "This is a test.";
        fwrite(data, 1, strlen(data), file);
        fclose(file);
    }
}

// File read benchmark function
void benchmark_file_read() {
    FILE *file = fopen("testfile.txt", "r");
    if (file) {
        char data[BUF_LEN];
        fread(data, 1, BUF_LEN, file);
        fclose(file);
    }
}

// Main function to execute benchmarks
int main() {
    printf("Benchmarking File System Operations:\n");

    measure_time(benchmark_file_creation, "File creation");
    measure_time(benchmark_file_write, "File write");
    measure_time(benchmark_file_read, "File read");
    measure_time(benchmark_file_deletion, "File deletion");

    return 0;
}


