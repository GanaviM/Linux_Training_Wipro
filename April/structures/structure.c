#include <stdio.h>

struct Student {
	char name[50];
	int rollNumber;
	float marks[5];
};

void studentRecord(struct Student *student){
	printf("Enter the Student Name: ");
	scanf("%s", student -> name);
	
	printf("Enter Roll number: ");
        scanf("%s", &student -> rollNumber);

	printf("Enter the marks for 5 subjects: \n");
	for (int i = 0; i < 5; i++)
	{
	       printf("Subject %d : ", i + 1);
       scanf("%f", &student -> marks[i]);
	}
}

void studentDetails(const struct Student *student)
{
	printf("\n Student Name: %s\n", student -> name);
	printf("Roll Number: %d\n", student -> rollNumber);
	printf("Marks in 5 subjects: \n");
	for(int i = 0; i < 5; ++i)
	{
		printf("Subject %d: %.2f\n", i + 1, student -> marks[i]);
	}
}

int main ()
{
	struct Student student;
	studentRecord(&student);
	studentDetails(&student);
	return 0;
}
