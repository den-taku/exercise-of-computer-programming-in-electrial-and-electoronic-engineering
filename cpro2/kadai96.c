#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
void relu(int n, const float *x, float *y);
void softmax(int n, const float *x, float *y);
float max(int n, const float *data);
void save(const char *filename, int m, int n, const float *A, const float *b);
void load(const char *filename, int m, int n, float *A, float *b);

int main(int argc, char *argv[]) {
	int n = 0;
	int m = 0;
	if (argc > 2) {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
	}
	float *A = malloc(sizeof(float) * m * n);
	float *b = malloc(sizeof(float) * n);
	load("test.dat", m, n, A, b);
	print(m, n, A);
	print(n, 1, b);
	free(A);
	free(b);
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

void relu(int n, const float *x, float *y) {
	rep(i, n) {
		if (x[i] > 0) {
			y[i] = x[i];
		} else {
			y[i] = 0;
		}
	}
}

void softmax(int n, const float *x, float *y) {
	float mx = max(n, x);
	float all = 0;
	rep(i, n) {
		float tmp = (float)exp((double)(x[i] - mx));
		y[i] = tmp;
		all += tmp;
	}
	rep(i, n)
	{
		y[i] /= all;
	}
}

float max(int n, const float *data) {
    float max = data[0];
	rep(i, n) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}

void save(const char *filename, int m, int n, const float *A, const float *b) {
	FILE *fp;
	fp = fopen(filename, "wr");
	if (!fp) {
		printf("%s cannot open", filename);
		return;
	}
	fwrite(A, sizeof(float), m * n, fp);
	fwrite(b, sizeof(float), n, fp);
	fclose(fp);
}

void load(const char *filename, int m, int n, float *A, float *b) {
	FILE *fp;
	fp = fopen(filename, "rb");
	if (!fp) {
		printf("%s cannot open", filename);
		return;
	}
	fread(A, sizeof(float), m * n, fp);
	fread(b, sizeof(float), n, fp);
	fclose(fp);
}