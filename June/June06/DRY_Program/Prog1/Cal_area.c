#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

// Function prototypes
double calculate_area_rectangle(double length, double width);
double calculate_perimeter_rectangle(double length, double width);
double calculate_area_circle(double radius);
double calculate_circumference_circle(double radius);
void print_result(const char* shape, const char* metric, double result);

int main() {
    double length = 10.0, width = 5.0;
    double radius = 7.0;

    // Rectangle calculations
    print_result("Rectangle", "Area", calculate_area_rectangle(length, width));
    print_result("Rectangle", "Perimeter", calculate_perimeter_rectangle(length, width));

    // Circle calculations
    print_result("Circle", "Area", calculate_area_circle(radius));
    print_result("Circle", "Circumference", calculate_circumference_circle(radius));

    return 0;
}

// Function to calculate the area of a rectangle
double calculate_area_rectangle(double length, double width) {
    return length * width;
}

// Function to calculate the perimeter of a rectangle
double calculate_perimeter_rectangle(double length, double width) {
    return 2 * (length + width);
}

// Function to calculate the area of a circle
double calculate_area_circle(double radius) {
    return PI * radius * radius;
}

// Function to calculate the circumference of a circle
double calculate_circumference_circle(double radius) {
    return 2 * PI * radius;
}

// Function to print the result of a calculation
void print_result(const char* shape, const char* metric, double result) {
    printf("%s %s: %.2f\n", shape, metric, result);
}
