#include <stdio.h>
#include <stdlib.h>
#include "gps_parser.h"

#define MAX_SENTENCES 100
#define MAX_SENTENCE_LENGTH 128

int main() {
    // Opening the sample data file
    FILE *file = fopen("sample_data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");//prints error message when no data is founf
        return 1;
    }

    // Read NMEA sentences from the file
    char sentences[MAX_SENTENCES][MAX_SENTENCE_LENGTH];
    int num_sentences = 0;
    while (fgets(sentences[num_sentences], MAX_SENTENCE_LENGTH, file) != NULL) {
        num_sentences++;
        if (num_sentences >= MAX_SENTENCES) {
            fprintf(stderr, "Maximum number of sentences exceeded.\n");
            break;
        }
    }
    fclose(file);

    // Parse each sentence and print the GPS data
    GPSDataPoint data;
    for (int i = 0; i < num_sentences; i++) {
        printf("Parsing sentence: %s", sentences[i]);
        parse_nmea_sentence(sentences[i], &data); // Parse the NMEA sentence
        print_gps_data(&data); // Print the parsed GPS data
        printf("\n");
    }

    return 0;
}
