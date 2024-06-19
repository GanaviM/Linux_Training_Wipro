#include <stdio.h>
#include <string.h>

void my_strcpy(char *dest, const char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

int main()
{
	char source[100], destination[100];

	printf("Enter source string:");
	fgets(source, sizeof(source), stdin);
	source[strcspn(source, "\n")] = '\0'; 

	my_strcpy(destination, source);

	printf("Copied string: %s\n", destination);

	return 0;
}
