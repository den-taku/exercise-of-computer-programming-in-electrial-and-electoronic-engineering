#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#include <stdio.h>
// #include "nn.h"

void print(int m, int n, const float *x);

int main() {
	// print(1, 10)
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