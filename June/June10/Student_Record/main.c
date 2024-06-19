#include <stdio.h>
#include "student.h"

int main() {
    StudentDatabase db;

    initializeDatabase(&db);

    addStudent(&db, 1, "Ganavi");
    addStudent(&db, 2, "Arjun");
    addStudent(&db, 3, "Adya");

    printf("Students in the database:\n");
    printStudents(&db);

    int index = searchStudent(&db, 2);
    if (index != -1)
        printf("\nFound student with ID 2: %s\n", db.students[index].name);
    else
        printf("\nStudent with ID 2 not found.\n");

    deleteStudent(&db, 2);

    printf("\nStudents in the database after deleting ID 2:\n");
    printStudents(&db);

    return 0;
}
