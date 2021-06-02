#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int m, int n, const float *x);
void print_oct(int m, int n, const float *x, const char * name);
void add(int n, const float *x, float *o);
void scale(int n, float x, float *o);
void init(int n, float x, float *o);
void rand_init(int n, float *o);

int main() {
    float y[64];
    print_oct(2, 3, y, "y");
    rand_init(6, y);
    print_oct(2, 3, y, "y");
    return 0;
}

void print(int m, int n, const float *x) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%.4f ", x[i * n + j]);
        }
        printf("\n");
    }
}

void print_oct(int m, int n, const float *x, const char * name) {
    int i, j;
    printf("%s = [", name);
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j) {
            printf(" %.4f ", x[i * n + j]);
        }
        printf(";\n");
    }
    printf("];\n");
}

void add(int n, const float *x, float *o) {
    int i;
    for (i = 0; i < n; ++i) {
        o[i] += x[i];
    }
}

void scale(int n, float x, float *o) {
    int i;
    for (i = 0; i < n; ++i) {
        o[i] *= x;
    }
}

void init(int n, float x, float *o) {
    int i;
    for (i = 0; i < n; ++i) {
        o[i] = x;
    }
}

void rand_init(int n, float *o) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < n; ++i)
    {
        o[i] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }
}