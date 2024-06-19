#include <stdio.h> //header files
#include <string.h>
#include "gps_parser.h" //.h file which we have added

void parse_nmea_sentence(const char *sentence, GPSDataPoint *data) {
    // Extract NMEA sentence type
    char type[6];
    sscanf(sentence, "$%5[^,]", type);

    // Check if the sentence type is GPRMC
    if (strcmp(type, "GPRMC") == 0) {
        char status;
        // Parse the NMEA sentence fields
        sscanf(sentence, "$GPRMC,%15[^,],%c,%15[^,],%c,%15[^,],%c,%f,%f,%15[^,],%f",
               data->timestamp, &status,
               data->latitude, &data->latitude[strlen(data->latitude)],
               data->longitude, &data->longitude[strlen(data->longitude)],
               &data->speed, &data->course,
               data->date, &data->magnetic_variation);

        // Ensure the latitude and longitude strings are null-terminated
        data->latitude[15] = '\0';
        data->longitude[15] = '\0';

        // Print error message if the status is not valid
        if (status != 'A') {
            printf("Invalid GPS data: %s\n", sentence);
        }
    } else {
        // Print error message for unsupported sentence types
        printf("Unsupported NMEA sentence type: %s\n", type);
    }
}

void print_gps_data(const GPSDataPoint *data) {
    // Print GPS data fields that matches to the sample data present in .txt file
    printf("Timestamp: %s\n", data->timestamp);
    printf("Latitude: %s\n", data->latitude);
    printf("Longitude: %s\n", data->longitude);
    printf("Speed: %.2f knots\n", data->speed);
    printf("Course: %.2f degrees\n", data->course);
    printf("Date: %s\n", data->date);
    printf("Magnetic Variation: %.2f degrees\n", data->magnetic_variation);
}
