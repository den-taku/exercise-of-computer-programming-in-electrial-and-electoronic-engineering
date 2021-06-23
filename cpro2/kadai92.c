#define rep(i, n) for (int i = 0; i < (int)(n); i++)
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
void bubble_sort(int n, float *array);
void swap(float *x, float *y);
void shuffle(int n, int *x);

int main(int argc, char *argv[]) {
	int n = 0;
	if (argc > 1) {
		n = atoi(argv[1]);
		float *y = malloc(sizeof(float) * n);
		rand_init(n, y);
		print(1, n, y);
		bubble_sort(n, y);
		print(1, n, y);
		int *index = malloc(sizeof(int) * n);
		rep(i, n) {
			index[i] = i;
		}
		shuffle(n, index);
		rep(i, n) {
			printf("%.4f ", y[index[i]]);
		}
		printf("\n");
		free(y);
		return 0;
	}
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

void bubble_sort(int n, float *array) {
	rep (i, n) {
		for (int j = n - 1; j >= i + 1; --j) {
			if (array[j] < array[j-1]) {
				swap(&array[j], &array[j - 1]);
			}
		}
	}
}

void swap(float *x, float *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void swap_int(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void shuffle(int n, int *x) {
    srand((unsigned int)time(NULL));
	rep(i, n) {
		int a = (int)rand() % n;
		int b = (int)rand() % n;
		swap_int(&x[a], &x[b]);
	}
}