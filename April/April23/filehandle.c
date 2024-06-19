#include <stdio.h>
#include <stdlib.h>
 
int main() {
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int read;
    printf("Contents of the file:\n");
    while ((read = fgetc(fp)) != EOF)
    {
	    putchar(read);
	}

    fprintf(fp, "Hello everyone.\n");

  
    // Close the file
    fclose(fp);

    return 0;
}

