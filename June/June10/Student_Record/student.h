#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[100];
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} StudentDatabase;

void initializeDatabase(StudentDatabase *db);
void addStudent(StudentDatabase *db, int id, const char *name);
int searchStudent(StudentDatabase *db, int id);
void deleteStudent(StudentDatabase *db, int id);
void printStudents(StudentDatabase *db);

#endif // STUDENT_H
