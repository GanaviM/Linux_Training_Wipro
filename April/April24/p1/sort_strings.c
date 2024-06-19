#include "sort_strings.h"

void sort(char *strings[], int nstrings) {
    char *temp;
    int i, j;

    for (i = 0; i < nstrings - 1; i++) {
        for (j = i + 1; j < nstrings; j++) {
            if (strcmp(strings[i], strings[j]) > 0) {
                temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
    }
}
