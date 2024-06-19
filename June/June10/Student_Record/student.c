#include <stdio.h>
#include <string.h>
#include "student.h"

// Initialize the student database
void initializeDatabase(StudentDatabase *db) {
    db->count = 0;
}

// Add a new student to the database
void addStudent(StudentDatabase *db, int id, const char *name) {
    if (db->count < MAX_STUDENTS) {
        db->students[db->count].id = id;
        strcpy(db->students[db->count].name, name);
        db->count++;
    } else {
        printf("Database is full. Cannot add more students.\n");
    }
}

// Search for a student by ID
int searchStudent(StudentDatabase *db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            return i; // Return the index of the student
        }
    }
    return -1; // Student not found
}

// Delete a student by ID
void deleteStudent(StudentDatabase *db, int id) {
    int index = searchStudent(db, id);
    if (index != -1) {
        for (int i = index; i < db->count - 1; i++) {
            db->students[i] = db->students[i + 1];
        }
        db->count--;
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

// Helper function to compare students by name
int compareStudents(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->name, studentB->name);
}

// Print the list of students sorted by name
void printStudents(StudentDatabase *db) {
    qsort(db->students, db->count, sizeof(Student), compareStudents);
    for (int i = 0; i < db->count; i++) {
        printf("ID: %d, Name: %s\n", db->students[i].id, db->students[i].name);
    }
}
