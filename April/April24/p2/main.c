#include <stdio.h>
#include "read_strings.h"
#include "sort_strings.h"
#include "write_strings.h"

#define MAX_STRINGS 128

int main() {
    char *strings[MAX_STRINGS];
    int nstrings;
    ReadStrings(strings, &nstrings, MAX_STRINGS, stdin);
    SortStrings(strings, nstrings);
    WriteStrings(strings, nstrings, stdout);
    return 0;
}
