#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH], subject[MAX_LINE_LENGTH];
    int id;

    // Open the file for reading
    file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read each line from the file
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Parse the line to extract name, ID, and subject
        if (sscanf(line, "%s %d %s", name, &id, subject) == 3) {
            // Print the parsed information with labels
            printf("Name: %s, ID: %d, Subject: %s\n", name, id, subject);
        } else {
            printf("Error parsing line: %s\n", line);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
