#include "write_strings.h"
#include <stdio.h>

void WriteStrings(char **strings, int nstrings, FILE *fp) {
    int i;
    for (i = 0; i < nstrings; i++)
        fprintf(fp, "%s", strings[i]);
}
