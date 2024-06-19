#include <stdio.h>

void ReadStrings(char **strings, int *nstrings, int maxstrings, FILE *fp);
void WriteStrings(char **strings, int nstrings, FILE *fp);
int CompareStrings(char *string1, char *string2);
void SortStrings(char **strings, int nstrings);
