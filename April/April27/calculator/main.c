// main_calculator.c

#include <stdio.h>
#include <dlfcn.h>

int main() {
    // Load the shared library
    void *lib_handle = dlopen("./libcalculator.so", RTLD_LAZY);
    if (!lib_handle) {
        // Error handling for library loading failure
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Function pointer declarations
    int (*add_func)(int, int);
    int (*subtract_func)(int, int);
    int (*multiply_func)(int, int);
    float (*divide_func)(int, int);

    // Get pointers to the calculator functions
    add_func = dlsym(lib_handle, "add");
    subtract_func = dlsym(lib_handle, "subtract");
    multiply_func = dlsym(lib_handle, "multiply");
    divide_func = dlsym(lib_handle, "divide");

    // Perform calculations
    int result_add = add_func(10, 5);
    int result_subtract = subtract_func(10, 5);
    int result_multiply = multiply_func(10, 5);
    float result_divide = divide_func(10, 5);

    // Print the results
    printf("Addition: %d\n", result_add);
    printf("Subtraction: %d\n", result_subtract);
    printf("Multiplication: %d\n", result_multiply);
    printf("Division: %.2f\n", result_divide);

    // Close the library
    dlclose(lib_handle);

    return 0;
}
