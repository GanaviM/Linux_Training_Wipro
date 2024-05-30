#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdbool.h>

// Structures
typedef struct File {
    char* name;         // Name of the file
    int size;           // Size of the file
    struct File* next;  // Pointer to the next file in the list
} File;

typedef struct Directory {
    char* name;                 // Name of the directory
    struct Directory* parent;  // Pointer to the parent directory
    struct Directory* subdirectories;  // Pointer to the first subdirectory
    File* files;               // Pointer to the first file in the directory
    struct Directory* next;    // Pointer to the next directory in the list
} Directory;

// Function declarations
void initializeFileSystem();  // Initialize the file system
void createDirectory(const char* name);  // Create a new directory
void createFile(const char* name, int size);  // Create a new file
void viewDirectoryContents(const char* directoryName);  // View contents of a directory
void navigateIntoDirectory(const char* directoryName);  // Navigate into a directory
void deleteFile(const char* fileName);  // Delete a file
void deleteDirectory(const char* directoryName);  // Delete a directory
void searchFile(const char* fileName);  // Search for a file

#endif
