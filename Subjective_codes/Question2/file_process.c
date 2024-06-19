#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100

// Global variables
char input_file[] = "input.txt";//We have created this file
char odd_output_file[] = "odd_output.txt"; //Output files
char even_output_file[] = "even_output.txt";// Output fikls
pthread_mutex_t mutex;

// Function prototypes
void *write_even_lines(void *arg);
void *write_odd_lines(void *arg);
void *read_even_file(void *arg);
void *read_odd_file(void *arg);

int main() {
    pthread_t write_thread1, write_thread2, read_thread1, read_thread2;

    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create threads for writing even and odd lines
    if (pthread_create(&write_thread1, NULL, write_even_lines, NULL) != 0 ||
        pthread_create(&write_thread2, NULL, write_odd_lines, NULL) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Wait for writing threads to finish
    pthread_join(write_thread1, NULL);
    pthread_join(write_thread2, NULL);

    // Create threads for reading even and odd files
    if (pthread_create(&read_thread1, NULL, read_even_file, NULL) != 0 ||
        pthread_create(&read_thread2, NULL, read_odd_file, NULL) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Wait for reading threads to finish
    pthread_join(read_thread1, NULL);
    pthread_join(read_thread2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

// Function to write even-numbered lines to the even_output_file
void *write_even_lines(void *arg) {
    FILE *input_fp, *output_fp;
    char line[MAX_LINE_LENGTH];
    int line_num = 0;

    // Open input and output files
    input_fp = fopen(input_file, "r");
    output_fp = fopen(even_output_file, "w");

    // Check if files opened successfully
    if (input_fp == NULL || output_fp == NULL) {
        perror("File opening failed");
        pthread_exit(NULL);
    }

    // Read input file line by line
    while (fgets(line, MAX_LINE_LENGTH, input_fp) != NULL) {
        // Write even-numbered lines to the output file
        if (line_num % 2 != 0) {
            pthread_mutex_lock(&mutex);
            fputs(line, output_fp);
            pthread_mutex_unlock(&mutex);
        }
        line_num++;
    }

    // Close files and exit thread
    fclose(input_fp);
    fclose(output_fp);
    pthread_exit(NULL);
}

// Function to write odd-numbered lines to the odd_output_file
void *write_odd_lines(void *arg) {
    FILE *input_fp, *output_fp;
    char line[MAX_LINE_LENGTH];
    int line_num = 0;

    // Open input and output files
    input_fp = fopen(input_file, "r");
    output_fp = fopen(odd_output_file, "w");

    // Check if files opened successfully
    if (input_fp == NULL || output_fp == NULL) {
        perror("File opening failed");
        pthread_exit(NULL);
    }

    // Read input file line by line
    while (fgets(line, MAX_LINE_LENGTH, input_fp) != NULL) {
        // Write odd-numbered lines to the output file
        if (line_num % 2 == 0) {
            pthread_mutex_lock(&mutex);
            fputs(line, output_fp);
            pthread_mutex_unlock(&mutex);
        }
        line_num++;
    }

    // Close files and exit thread
    fclose(input_fp);
    fclose(output_fp);
    pthread_exit(NULL);
}

// Function to read and print the contents of the even_output_file
void *read_even_file(void *arg) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];

    // Open the even_output_file
    fp = fopen(even_output_file, "r");

    // Check if file opened successfully
    if (fp == NULL) {
        perror("File opening failed");
        pthread_exit(NULL);
    }

    // Print the contents of the even_output_file
    printf("Contents of even_output.txt:\n");
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        printf("%s", line);
    }

    // Close file and exit thread
    fclose(fp);
    pthread_exit(NULL);
}

// Function to read and print the contents of the odd_output_file
void *read_odd_file(void *arg) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];

    // Open the odd_output_file
    fp = fopen(odd_output_file, "r");

    // Check if file opened successfully
    if (fp == NULL) {
        perror("File opening failed");
        pthread_exit(NULL);
    }

    // Print the contents of the odd_output_file
    printf("Contents of odd_output.txt:\n");
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        printf("%s", line);
    }

    // Close file and exit thread
    fclose(fp);
    pthread_exit(NULL);
}
