#include "file_system.h" // Include header file for file system definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables for root directory and current directory
Directory* rootDirectory = NULL; // Declare a pointer to the root directory, initially set to NULL
Directory* currentDirectory = NULL; // Declare a pointer to the current directory, initially set to NULL

// Function to initialize the file system
void initializeFileSystem() {
    rootDirectory = (Directory*)malloc(sizeof(Directory)); // Allocate memory for the root directory
    rootDirectory->name = strdup("root"); // Set the name of the root directory
    rootDirectory->parent = NULL; // Set the parent directory of the root directory to NULL
    rootDirectory->subdirectories = NULL; // Set the subdirectories of the root directory to NULL
    rootDirectory->files = NULL; // Set the files in the root directory to NULL
    rootDirectory->next = NULL; // Set the next pointer of the root directory to NULL

    currentDirectory = rootDirectory; // Set the current directory to the root directory
}

// Function to create a new directory
void createDirectory(const char* name) {
    Directory* newDirectory = (Directory*)malloc(sizeof(Directory)); // Allocate memory for the new directory
    newDirectory->name = strdup(name); // Set the name of the new directory
    newDirectory->parent = currentDirectory; // Set the parent directory of the new directory to the current directory
    newDirectory->subdirectories = NULL; // Set the subdirectories of the new directory to NULL
    newDirectory->files = NULL; // Set the files in the new directory to NULL
    newDirectory->next = NULL; // Set the next pointer of the new directory to NULL

    // Add the new directory to the list of subdirectories in the current directory
    if (currentDirectory->subdirectories == NULL) {
        currentDirectory->subdirectories = newDirectory;
    } else {
        Directory* temp = currentDirectory->subdirectories;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newDirectory;
    }
}

// Function to create a new file
void createFile(const char* name, int size) {
    File* newFile = (File*)malloc(sizeof(File)); // Allocate memory for the new file
    newFile->name = strdup(name); // Set the name of the new file
    newFile->size = size; // Set the size of the new file
    newFile->next = NULL; // Set the next pointer of the new file to NULL

    // Add the new file to the list of files in the current directory
    if (currentDirectory->files == NULL) {
        currentDirectory->files = newFile;
    } else {
        File* temp = currentDirectory->files;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFile;
    }
}

// Function to view the contents of a directory
void viewDirectoryContents(const char* directoryName) {
    Directory* temp = currentDirectory->subdirectories; // Initialize a temporary pointer to traverse subdirectories
    while (temp != NULL) {
        printf("Directory: %s\n", temp->name); // Print the name of each subdirectory
        temp = temp->next; // Move to the next subdirectory
    }

    File* fileTemp = currentDirectory->files; // Initialize a temporary pointer to traverse files
    while (fileTemp != NULL) {
        printf("File: %s, Size: %d\n", fileTemp->name, fileTemp->size); // Print the name and size of each file
        fileTemp = fileTemp->next; // Move to the next file
    }
}

// Function to navigate into a directory
void navigateIntoDirectory(const char* directoryName) {
    Directory* temp = currentDirectory->subdirectories; // Initialize a temporary pointer to traverse subdirectories
    while (temp != NULL) {
        if (strcmp(temp->name, directoryName) == 0) { // Check if the name of the subdirectory matches the given name
            currentDirectory = temp; // Set the current directory to the matched subdirectory
            return; // Exit the function
        }
        temp = temp->next; // Move to the next subdirectory
    }
    printf("Directory not found.\n"); // Print a message if the directory is not found
}

// Function to delete a file
void deleteFile(const char* fileName) {
    File* temp = currentDirectory->files; // Initialize a temporary pointer to traverse files
    File* prev = NULL; // Initialize a pointer to keep track of the previous file
    while (temp != NULL) {
        if (strcmp(temp->name, fileName) == 0) { // Check if the name of the file matches the given name
            if (prev == NULL) { // If the file to be deleted is the first in the list
                currentDirectory->files = temp->next; // Update the head of the file list
            } else {
                prev->next = temp->next; // Link the previous file to the next file, skipping the current file
            }
            free(temp->name); // Free the memory allocated for the name of the file
            free(temp); // Free the memory allocated for the file
            return; // Exit the function
        }
        prev = temp; // Move the previous pointer to the current file
        temp = temp->next; // Move to the next file
    }
    printf("File not found.\n"); // Print a message if the file is not found
}

// Function to delete a directory
void deleteDirectory(const char* directoryName) {
    Directory* temp = currentDirectory->subdirectories; // Initialize a temporary pointer to traverse subdirectories
    Directory* prev = NULL; // Initialize a pointer to keep track of the previous directory
    while (temp != NULL) {
        if (strcmp(temp->name, directoryName) == 0) { // Check if the name of the directory matches the given name
            if (prev == NULL) { // If the directory to be deleted is the first in the list
                currentDirectory->subdirectories = temp->next; // Update the head of the directory list
            } else {
                prev->next = temp->next; // Link the previous directory to the next directory, skipping the current directory
            }
            free(temp->name); // Free the memory allocated for the name of the directory
            free(temp); // Free the memory allocated for the directory
            return; // Exit the function
        }
        prev = temp; // Move the previous pointer to the current directory
        temp = temp->next; // Move to the next directory
    }
    printf("Directory not found.\n"); // Print a message if the directory is not found
}

// Function to search for a file
void searchFile(const char* fileName) {
    File* temp = currentDirectory->files; // Initialize a temporary pointer to traverse files
    while (temp != NULL) {
        if (strcmp(temp->name, fileName) == 0) { // Check if the name of the file matches the given name
            printf("File found: %s, Size: %d\n", temp->name, temp->size); // Print the name and size of the file
            return; // Exit the function
        }
        temp = temp->next; // Move to the next file
    }
    printf("File not found.\n"); // Print a message if the file is not found
}
