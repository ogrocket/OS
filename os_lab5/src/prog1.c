#include "../inc/liblab.h"

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

int main() {

    printf("prog1.c: Shared library - Dynamic Linking\n");
    printName();

    int cmd = 0;

    int array[20];
    const unsigned int SIZE = 20;
    initArray(array, SIZE);

    float A = 0.0f;
    float deltaX = 0.0f;

    while (scanf("%d", &cmd) != EOF) {
        switch (cmd) {
        case 0:
            printf("Not supported for Dynamic linking\n");
            break;
        case 1:
            scanf("%f %f", &A, &deltaX);
            printf("Calling: float Derivative(float A, float deltaX);\n\tresult: %f\n", Derivative(A, deltaX));
            break;
        case 2:
            printf("Array: ");
            printArray(array, SIZE);
            printf("\n");
            Sort(array, SIZE);
            printf("Calling: int* Sort(int* array, unsigned int size);\n\tresult: ");
            printArray(array, SIZE);
            printf("\n");
            initArray(array, SIZE);
            break;
        }
    }
    return 0;
}