#include "nn.h"
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#include <stdio.h>

void print(int m, int n, const float *x);
void fc(int m, int n, const float *x, const float *A, const float *b, float *y);
void relu(int n, const float *x, float *y);
float max(int n, const float *data);
void softmax(int n, const float *x, float *y);
size_t max_index(int n, const float *data);
int interface3(const float *A, const float *b, const float *x);
void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dEdx);
void relu_bwd(int n, const float *x, const float *dEdy, float *dEdx);
void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx);
void copy(int n, const float *x, float *y);
void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dEdA, float *dEdb);

int main() {
	float *train_x = NULL;
	unsigned char *train_y = NULL;
	int train_count = -1;
	float *test_x = NULL;
	unsigned char *test_y = NULL;
	int test_count = -1;
	int width = -1;
	int height = -1;
	load_mnist(&train_x, &train_y, &train_count, 
		&test_x, &test_y, &test_count, 
		&width, &height);
	#if 0
	  volatile float x = 0;
	  volatile float y = 0;
	  volatile float z = x/y;
	#endif

	// int sum = 0;
	// rep(i, test_count) {
	// 	if(interface3(A_784x10, b_784x10, test_x + i * width * height) == test_y[i]) {
	// 		++sum;
	// 	}
	// }
	// printf("%f%%\n", sum * 100.0 / test_count);

	float *y = malloc(sizeof(float) * 10);
	float *dEdA = malloc(sizeof(float) * 784 * 10);
	float *dEdb = malloc(sizeof(float) * 10);
	backward3(A_784x10, b_784x10, train_x + 784 * 8, train_y[8], y, dEdA, dEdb);
	print(10, 784, dEdA);
	print(1, 10, dEdb);

	// print(1, 10, y);

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

void fc(int m, int n, const float *x, const float *A, const float *b, float *y) {
    int i, j;
    for (i = 0; i < m; ++i) {
        y[i] = b[i];
        for (j = 0; j < n; ++j) {
            y[i] += A[i * n + j] * x[j];
        }
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

float max(int n, const float *data) {
    float max = data[0];
	rep(i, n) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}

void softmax(int n, const float *x, float *y) {
	float mx = max(n, x); // Θ(n)
	float all = 0;
	rep(i, n) { // Θ(n * exp_cal)
		float tmp = (float)exp((double)(x[i] - mx));
		y[i] = tmp;
		all += tmp;
	}
	rep(i, n) { // Θ(n)
		y[i] /= all;
	}
}

size_t max_index(int n, const float *data) {
    float max = data[0];
	size_t max_index = 0;
	rep(i, n) {
		if (data[i] > max) {
			max = data[i];
			max_index = i;
		}
	}
	return max_index;
}

int interface3(const float *A, const float *b, const float *x) {
	float *y = malloc(sizeof(float) * 10);
	// A: 10x784, b: 10, x: 784
	fc(10, 784, x, A, b, y);
	relu(10, y, y);
	softmax(10, y, y);
	return (int)max_index(10, y);
}

// no tests
void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dEdx) {
	float *y_k = malloc(sizeof(float) * n);
	softmax(n, y, y_k);
	rep(i, n) {
		dEdx[i] = y_k[i] - t;
	}
}

// no tests
void relu_bwd(int n, const float *x, const float *dEdy, float *dEdx) {
	rep(i, x) {
		if (x[i] > 0.0) {
			dEdx[i] = dEdy[i];
		} else {
			dEdx[i] = 0.0;
		}
	}
}

// no tests
void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx){
	rep(i, m) {
		rep(j, n) {
			dEdA[i * n + j] = dEdy[i] * x[j];

		}
		dEdb[i] = dEdy[i];
	}
	rep(i, n) {
		dEdx[i] = 0.0;
		rep(j, m) {
			dEdx[i] += A[j * n + i] * dEdy[j];
		}
    }
	
}

void copy(int n, const float *x, float *y) {
	rep(i, n) {
		y[i] = x[i];
	}
}

// TODO: here
void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dEdA, float *dEdb) {
	// float *y = malloc(sizeof(float) * 10);
	// A: 10x784, b: 10, x: 784
	fc(10, 784, x, A, b, y);
	float *tmp_y = malloc(sizeof(float) * 10);
	copy(10, y, tmp_y);
	float *tmp_x = malloc(sizeof(float) * 784);
	copy(784, y, tmp_x);
	relu(10, y, y);
	softmax(10, y, y);
	// return (int)max_index(10, y);
}

//   // これ以降，３層NN の係数 A_784x10 および b_784x10 と，
//   // 訓練データ train_x + 784*i (i=0,...,train_count-1), train_y[0]～train_y[train_count-1],
//   // テストデータ test_x + 784*i (i=0,...,test_count-1), test_y[0]～test_y[test_count-1],
//   // を使用することができる．
