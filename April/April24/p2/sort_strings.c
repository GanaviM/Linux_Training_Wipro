#include "compare_strings.h"
#include "sort_strings.h"

void SortStrings(char **strings, int nstrings) {
    int i, j;
    for (i = 0; i < nstrings; i++) {
        for (j = i+1; j < nstrings; j++) {
            if (CompareStrings(strings[i], strings[j]) > 0) {
                char *swap = strings[i];
                strings[i] = strings[j];
                strings[j] = swap;
            }
        }
    }
}
