#include <stdio.h>
#include <math.h>

void printName() {
    printf("liblab_first.c\n");
}

// Рассчет производной функции cos(x) в точке A с приращением deltaX
extern float Derivative(float A, float deltaX) {
    if (deltaX == 0.0) {
        printf("NAN\n");
        return NAN;
    }
    return (cos(A + deltaX) - cos(A)) / deltaX;
}

// Отсортировать целочисленный массив
extern int* Sort(int* array, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j + 1] < array[j]) {
                int tmp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tmp;
            }
        }
    }
    return array;
}