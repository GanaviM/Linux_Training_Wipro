#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *lib_handle = dlopen("./libcalculator.so", RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    int (*add_func)(int, int) = dlsym(lib_handle, "add");
    int (*subtract_func)(int, int) = dlsym(lib_handle, "subtract");
    int (*multiply_func)(int, int) = dlsym(lib_handle, "multiply");
    float (*divide_func)(int, int) = dlsym(lib_handle, "divide");

    int result_add = add_func(10, 5);
    int result_subtract = subtract_func(10, 5);
    int result_multiply = multiply_func(10, 5);
    float result_divide = divide_func(10, 5);

    printf("Addition: %d\n", result_add);
    printf("Subtraction: %d\n", result_subtract);
    printf("Multiplication: %d\n", result_multiply);
    printf("Division: %.2f\n", result_divide);

    dlclose(lib_handle);

    return 0;
}
