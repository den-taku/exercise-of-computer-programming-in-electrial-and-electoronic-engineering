#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void print(int m, int n, const float *x);
static void fc(int m, int n, const float *x, const float *A, const float *b, float *y);
static void relu(int n, const float *x, float *y);
static float max(int n, const float *data);
static void softmax(int n, const float *x, float *y);
static size_t max_index(int n, const float *data);
static int inference3(const float *A, const float *b, const float *x, float *y);
static void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dEdx);
static void relu_bwd(int n, const float *x, const float *dEdy, float *dEdx);
static void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx);
static void copy(int n, const float *x, float *y);
static void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dEdA, float *dEdb);
static void swap_int(int *x, int *y);
static void shuffle(int n, int *x);
static float cross_entoropy_error(const float *y, int t);
static void add(int n, const float *x, float *o);
static void scale(int n, float x, float *o);
static void init(int n, float x, float *o);
static void rand_init(int n, float *o);

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

	const int epoch = 10;
	const int mini_batch = 100;
	const float learning_rate = 0.1;

	float *A = malloc(sizeof(float) * 784 * 10);
	float *b = malloc(sizeof(float) * 10);
	rand_init(784 * 10, A);
	rand_init(10, b);

	int *index = malloc(sizeof(int) * train_count);
	rep(i, train_count) {
		index[i] = i;
	}

	float *dEdA_ave = malloc(sizeof(float) * 784 * 10);
	float *dEdb_ave = malloc(sizeof(float) * 10);
	float *y = malloc(sizeof(float) * 10);
	float *dEdA = malloc(sizeof(float) * 784 * 10);
	float *dEdb = malloc(sizeof(float) * 10);

	rep(i, epoch) {
		// train
		printf("epoch: %d\n", i);
		printf("	training...\n");
		shuffle(train_count, index);
		rep(j, train_count / mini_batch) {
			init(784 * 10, 0.0, dEdA_ave);
			init(10, 0.0, dEdb_ave);
			rep(k, mini_batch) {
				backward3(A, b, train_x + 784 * index[j * mini_batch + k], train_y[index[j * mini_batch + k]], y, dEdA, dEdb);
				add(784 * 10, dEdA, dEdA_ave);
				add(10, dEdb, dEdb_ave);
			}
			const float coefficient = (train_count / mini_batch) * learning_rate * (-1.0);
			scale(784 * 10, coefficient, dEdA_ave);
			scale(10, coefficient, dEdb_ave);
			add(784 * 10, dEdA_ave, A);
			add(10, dEdb_ave, b);
		}
		// test
		printf("	testing..\n");
		int sum = 0;
		float error = 0.0;
		rep(i, test_count) {
			if (inference3(A, b, test_x + i * width * height, y) == test_y[i]) {
				++sum;
			}
			error += cross_entoropy_error(y, test_y[i]);
		}
		printf("		correct answer: %f%%\n", sum * 100.0 / test_count);
		printf("		cross entropy : %f\n", error * 100.0 / test_count);
	}

	free(A);
	free(b);
	free(index);
	free(dEdA_ave);
	free(dEdb_ave);
	free(y);
	free(dEdA);
	free(dEdb);

	// int sum = 0;
	// float *y = malloc(sizeof(float) * 10);
	// rep(i, test_count) {
	// 	if(inference3(A_784x10, b_784x10, test_x + i * width * height, y) == test_y[i]) {
	// 		++sum;
	// 	}
	// }
	// free(y);
	// printf("%f%%\n", sum * 100.0 / test_count);

	// float *y = malloc(sizeof(float) * 10);
	// float *dEdA = malloc(sizeof(float) * 784 * 10);
	// float *dEdb = malloc(sizeof(float) * 10);
	// backward3(A_784x10, b_784x10, train_x + 784 * 8, train_y[8], y, dEdA, dEdb);
	// print(10, 784, dEdA);
	// print(1, 10, dEdb);
	// free(y);
	// free(dEdA);
	// free(dEdb);

	// int *index = malloc(sizeof(int) * train_count);
	// rep(i, train_count) {
	// 	index[i] = i;
	// }
	// shuffle(train_count, index);
	// free(index);

	// print(1, 10, y);

	return 0;
}

inline static void print(int m, int n, const float *x) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%.4f ", x[i * n + j]);
        }
        printf("\n");
    }
}

inline static void fc(int m, int n, const float *x, const float *A, const float *b, float *y) {
    int i, j;
    for (i = 0; i < m; ++i) {
        y[i] = b[i];
        for (j = 0; j < n; ++j) {
            y[i] += A[i * n + j] * x[j];
        }
    } 
}

inline static void relu(int n, const float *x, float *y) {
	rep(i, n) {
		y[i] = (x[i] > 0.0) ? x[i] : 0.0;
		// if (x[i] > 0) {
		// 	y[i] = x[i];
		// } else {
		// 	y[i] = 0;
		// }
	}
}

inline static float max(int n, const float *data) {
    float max = data[0];
	rep(i, n) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}

inline static void softmax(int n, const float *x, float *y) {
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

inline static size_t max_index(int n, const float *data) {
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

inline static int inference3(const float *A, const float *b, const float *x, float *y) {
	// float *y = malloc(sizeof(float) * 10);
	// A: 10x784, b: 10, x: 784
	fc(10, 784, x, A, b, y);
	relu(10, y, y);
	softmax(10, y, y);
	int max = (int)max_index(10, y);
	// free(y);
	return max;
}

inline static void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dEdx) {
	copy(n, y, dEdx);
	dEdx[t] -= 1.0;
}

inline static void relu_bwd(int n, const float *x, const float *dEdy, float *dEdx) {
	rep(i, n) {
		dEdx[i] = (x[i] > 0.0) ? dEdy[i] : 0.0;
		// if (x[i] > 0.0) {
		// 	dEdx[i] = dEdy[i];
		// } else {
		// 	dEdx[i] = 0.0;
		// }
	}
}

// no tests
inline static void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx){
	rep(i, m) {
		rep(j, n) {
			// dE/da = dE/dy * x^T
			dEdA[i * n + j] = dEdy[i] * x[j];

		}
		// dE/db = dE/dk
		dEdb[i] = dEdy[i];
	}
	// dE/dx = a^T * dE/dy
	rep(i, n) {
		dEdx[i] = 0.0;
		rep(j, m) {
			dEdx[i] += A[j * n + i] * dEdy[j];
		}
    }
	
}

inline static void copy(int n, const float *x, float *y) {
	rep(i, n) {
		y[i] = x[i];
	}
}

inline static void backward3(const float *A, const float *b, const float *x, unsigned char t, float *y, float *dEdA, float *dEdb) {
	// A: 10x784, b: 10, x: 784
	fc(10, 784, x, A, b, y);
	float *tmp_x = malloc(sizeof(float) * 784); // TODO : Check
	copy(784, y, tmp_x);
	relu(10, y, y);
	softmax(10, y, y);
	// return (int)max_index(10, y);

	float *dEdx_tmp = malloc(sizeof(float) * 784); // TODO : Check
	softmaxwithloss_bwd(10, y, t, dEdx_tmp);
	relu_bwd(10, tmp_x, dEdx_tmp, dEdx_tmp);
	float *dEdx = malloc(sizeof(float) * 784);
	fc_bwd(10, 784, x, dEdx_tmp, A, dEdA, dEdb, dEdx);
	free(tmp_x);
	free(dEdx_tmp);
	free(dEdx);
}

inline static void swap_int(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

// no tests
inline static void shuffle(int n, int *x) {
    srand((unsigned int)time(NULL));
	rep(i, n) {
		int j = (int)rand() % n;
		swap_int(&x[i], &x[j]);
	}
}

// no tests
inline static float cross_entoropy_error(const float *y, int t) {
	return -log(y[t] + 1e-7);
}

inline static void add(int n, const float *x, float *o) {
    int i;
    for (i = 0; i < n; ++i) {
        o[i] += x[i];
    }
}

inline static void scale(int n, float x, float *o) {
    int i;
    for (i = 0; i < n; ++i) {
        o[i] *= x;
    }
}

inline static void init(int n, float x, float *o) {
    int i;
    for (i = 0; i < n; ++i) {
        o[i] = x;
    }
}

inline static void rand_init(int n, float *o) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < n; ++i)
    {
        o[i] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }
}

//   // これ以降，３層NN の係数 A_784x10 および b_784x10 と，
//   // 訓練データ train_x + 784*i (i=0,...,train_count-1), train_y[0]～train_y[train_count-1],
//   // テストデータ test_x + 784*i (i=0,...,test_count-1), test_y[0]～test_y[test_count-1],
//   // を使用することができる．
