#include <stdio.h>
#include <stdlib.h>
#include "sort_strings.h"

#define MAX_STRINGS 5
#define MAX_LENGTH 256

int main() {
    char *strings[MAX_STRINGS];
    char input[MAX_LENGTH];
    int nstrings = 0;

    printf("Enter %d strings:\n", MAX_STRINGS);
    for (int i = 0; i < MAX_STRINGS; i++) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            return 1;
        }
        strings[i] = strdup(input);
        nstrings++;
    }

    sort(strings, nstrings);

    printf("Sorted strings:\n");
    for (int i = 0; i < nstrings; i++) {
        printf("%s", strings[i]);
        free(strings[i]); // Free memory allocated by strdup
    }

    return 0;
}
