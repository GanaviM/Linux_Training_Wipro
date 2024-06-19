#ifndef GPS_PARSER_H
#define GPS_PARSER_H

// Structure that contains the GPS data (sample data is taken in .txt file)
typedef struct {
    char latitude[16];              // Latitude
    char longitude[16];             // Longitude
    char timestamp[16];             // Timestamp
    float speed;                    // Speed in knots
    float course;                   // Course angle in degrees
    char date[16];                  // Date of the fix
    float magnetic_variation;       // Magnetic variation in degrees
} GPSDataPoint;

// Function to parse an NMEA sentence and extract GPS data
void parse_nmea_sentence(const char *sentence, GPSDataPoint *data);

// Function to print GPS data
void print_gps_data(const GPSDataPoint *data);

#endif
