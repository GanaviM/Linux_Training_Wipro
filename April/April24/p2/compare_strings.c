#include "compare_strings.h"

int CompareStrings(char *string1, char *string2) {
    char *p1 = string1;
    char *p2 = string2;
    while (*p1 && *p2) {
        if (*p1 < *p2) return -1;
        else if (*p1 > *p2) return 1;
        p1++;
        p2++;
    }
    return 0;
}
