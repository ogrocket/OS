#include "../inc/liblab.h"

#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>

void printArray(int* a, unsigned int s) {
    for (unsigned int i = 0; i < s; ++i) {
        printf("%d ", a[i]);
    }
}

void initArray(int* a, unsigned int s) {
    for (unsigned int i = 0; i < s; ++i) {
        a[i] = rand() % 100;
    }
}

const char libname_first[] = "./lib/liblab_first.so";
const char libname_second[] = "./lib/liblab_second.so";

char* error = NULL;

void get_function(void* dl_hdl, const char* name, void** func_ptr) {
    *func_ptr = dlsym(dl_hdl, name);
    error = dlerror();
    if (error != NULL) {
        printf("dlsym() %s\n", error);
        exit(13);
    }
}

void get_handle(const char* libname, void** dl_hdl) {
    *dl_hdl = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
    if (*dl_hdl == NULL) {
        printf("dlopen() error %s\n", dlerror());
        exit(12);
    }
}

#define SIZE 20

int main() {

    printf("prog1.c: Shared library - Dynamic Loading\n");

    float (*Derivative_ptr)(float, float) = NULL;
    int* (*Sort_ptr)(int*, unsigned int) = NULL;
    void* (*printName_ptr)() = NULL;

    void* dl_handles[2];
    get_handle(libname_first, &dl_handles[0]);
    printf("god handle 1: %p\n", dl_handles[0]);
    get_handle(libname_second, &dl_handles[1]);
    printf("god handle 2: %p\n", dl_handles[1]);

    int cmd = 0;
    int curr = 0;

    get_function(dl_handles[curr], "Derivative", (void**)(&Derivative_ptr));
    get_function(dl_handles[curr], "Sort", (void**)(&Sort_ptr));
    get_function(dl_handles[curr], "printName", (void**)(&printName_ptr));

    printName_ptr();

    int array[SIZE];
    initArray(array, SIZE);

    float A = 0.0f;
    float deltaX = 0.0f;

    while (scanf("%d", &cmd) != EOF) {
        switch (cmd) {
        case 0:
            printf("Supported for Dynamic loading. Switching...\n");

            curr ^= 1;

            get_function(dl_handles[curr], "Derivative", (void**)(&Derivative_ptr));
            get_function(dl_handles[curr], "Sort", (void**)(&Sort_ptr));
            get_function(dl_handles[curr], "printName", (void**)(&printName_ptr));

            printName_ptr();

            break;
        case 1:
            scanf("%f %f", &A, &deltaX);
            printf("Calling: float Derivative(float A, float deltaX);\n\tresult: %f\n", Derivative_ptr(A, deltaX));
            break;
        case 2:
            printf("Array: ");
            printArray(array, SIZE);
            printf("\n");
            Sort_ptr(array, SIZE);
            printf("Calling: int* Sort(int* array, unsigned int size);\n\tresult: ");
            printArray(array, SIZE);
            printf("\n");
            initArray(array, SIZE);
            break;
        }
    }

    if (dlclose(dl_handles[0])
        || dlclose(dl_handles[1])) {
        exit(15);
    }
    return 0;
}