#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int m, int n, const float *x);
void print_oct(int m, int n, const float *x, const char * name);
void add(int n, const float *x, float *o);
void scale(int n, float x, float *o);
void init(int n, float x, float *o);
void rand_init(int n, float *o);
void mul(int m, int n, const float *x, const float *A, float *o);
void fc(int m, int n, const float *x, const float *A, const float *b, float *o);

int main() {
    float A[6] = {1, 2, 3, 4, 5, 6};
    float b[2] = {0.5, 0.25};
    float x[3] = {2, 3, 5};
    float o[2];
    fc(2, 3, x, A, b, o);
    print_oct(2, 3, A, "A");
    print_oct(2, 1, b, "b");
    print_oct(3, 1, x, "x");
    print_oct(2, 1, o, "o");
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

void mul(int m, int n, const float *x, const float *A, float *o) {
    int i, j;
    for (i = 0; i < m; ++i) {
        o[i] = 0;
        for (j = 0; j < n; ++j) {
            o[i] += A[i * n + j] * x[j];
        }
    }
}

void fc(int m, int n, const float *x, const float *A, const float *b, float *o) {
    int i, j;
    for (i = 0; i < m; ++i) {
        o[i] = b[i];
        for (j = 0; j < n; ++j) {
            o[i] += A[i * n + j] * x[j];
        }
    } 
}