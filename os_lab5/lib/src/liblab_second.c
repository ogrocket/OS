#include <stdio.h>
#include <math.h>

void printName() {
    printf("liblab_second.c\n");
}

//f'(x) = (f(A + deltaX) – f(A-deltaX))/ (2*deltaX)
// Рассчет производной функции cos(x) в точке A с приращением deltaX
extern float Derivative(float A, float deltaX) {
    if (deltaX == 0.0) {
        printf("NAN\n");
        return NAN;
    }
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}

unsigned int partition(int* a, unsigned int l, unsigned int r) {
    int p = (r + l) / 2;
    unsigned int i = l;
    unsigned int j = r;
    while (i < j) {
        while (a[i] <= a[p] && i < r) {
            i++;
        }
        while (a[j] > a[p]) {
            j--;
        }
        if (i >= j)
            break;
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    int tmp = a[p];
    a[p] = a[j];
    a[j] = tmp;
    return j;
}

int* quicksort(int* a, unsigned int l, unsigned int r) {
    if (l < r) {
        unsigned int p = partition(a, l, r);
        quicksort(a, l, p - 1);
        quicksort(a, p + 1, r);
    }
    return a;
}

// Отсортировать целочисленный массив
extern int* Sort(int* array, unsigned int size) {
    return quicksort(array, 0, size - 1);
}