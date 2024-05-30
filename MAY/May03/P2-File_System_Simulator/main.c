#include <stdio.h>
#include <time.h> // Include the time.h header for clock function
#include "file_system.h"

// Declare currentDirectory as an extern variable
extern Directory* currentDirectory;

int main() {
    clock_t start, end; // Variables to store start and end CPU time

    // Initialize the file system
    initializeFileSystem();

    // Create some directories and files
    createDirectory("documents");
    createDirectory("images");
    createFile("document1.txt", 100);
    createFile("image1.jpg", 500);

    // Print the current directory contents
    printf("Current directory contents:\n");
    viewDirectoryContents(currentDirectory->name);

    // Start measuring CPU time
    start = clock();

    // Navigate into 'documents' directory and create a file
    printf("\nNavigating into 'documents' directory...\n");
    navigateIntoDirectory("documents");
    createFile("document2.txt", 200);

    // Stop measuring CPU time
    end = clock();

    // Calculate CPU time elapsed
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Print the elapsed CPU time
    printf("\nCPU time used: %.6f seconds\n", cpu_time_used);

    // Print the current directory contents again
    printf("\nCurrent directory contents:\n");
    viewDirectoryContents(currentDirectory->name);

    // Search for a file
    printf("\nSearching for 'image1.jpg'...\n");
    searchFile("image1.jpg");

    // Delete a file
    printf("\nDeleting 'document1.txt'...\n");
    deleteFile("document1.txt");

    // Print the current directory contents one more time
    printf("\nCurrent directory contents:\n");
    viewDirectoryContents(currentDirectory->name);

    return 0;
}

