#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*RegisterFunc)(void);
typedef struct {
    RegisterFunc register_func;
    void (*callback_func)(int);
} Module;

void register_module() {
    printf("Module registered successfully!\n");
}

void callback_function(int value) {
    printf("Callback: Received value: %d\n", value);
}

int main() {
    void *handle;
    Module module;
    RegisterFunc register_func;
    handle = dlopen("./libmodule.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }
    register_func = (RegisterFunc)dlsym(handle, "register_module");
    if (!register_func) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    register_func();
    module.callback_func = callback_function;
    module.callback_func(42);
    if (dlclose(handle) != 0) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }
     return 0;
}
