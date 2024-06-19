#include <stdio.h>
#include <dlfcn.h>

// Function prototypes
void load_and_execute(const char *library_path, const char *function_name);

int main() {
    // Call the function to load and execute dynamically
    load_and_execute("./libexample.so", "hello_dynamic");

    return 0;
}

// Function to load and execute a function from a shared library dynamically
void load_and_execute(const char *library_path, const char *function_name) {
    // Load the shared library
    void *lib_handle = dlopen(library_path, RTLD_LAZY);
    if (!lib_handle) {
        // Error handling for library loading failure
        fprintf(stderr, "Error: %s\n", dlerror());
        return;
    }
 
    // Get a pointer to the function
    void (*dynamic_function)() = dlsym(lib_handle, function_name);
    if (!dynamic_function) {
        // Error handling for function symbol retrieval failure
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(lib_handle); // Close the library
        return;
    }
 
    // Call the function
    dynamic_function();
 
    // Close the library
    dlclose(lib_handle);
}

