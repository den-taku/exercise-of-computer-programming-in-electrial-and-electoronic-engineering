#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// static void print(int m, int n, const float *x);
// static void print_int(int m, int n, const int *x);
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
static int inference6(const float *A1, const float *b1, const float *A2, const float *b2, const float *A3, const float *b3, const float *x, float *y);
static void backward6(const float *A1, const float *b1, const float *A2, const float *b2, const float *A3, const float *b3, const float *x, unsigned char t, float *y, float *dEdA1, float *dEdb1, float *dEdA2, float *dEdb2, float *dEdA3, float *dEdb3);
static void save(const char *filename, int m, int n, const float *A, const float *b);
static void load(const char *filename, int m, int n, float *A, float *b);

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
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
    const float coefficient = -1.0 * learning_rate / (float)mini_batch;

    int *index = NULL;
    float *y = NULL;
    float *x = NULL;

    int sum;
    float error;

    int input;
    char filename[256];

    float *A = NULL;
    float *b = NULL;
    float *dEdA_ave = NULL;
    float *dEdb_ave = NULL;
    float *dEdA = NULL;
    float *dEdb = NULL;

    float *A1 = NULL;
    float *A2 = NULL;
    float *A3 = NULL;
    float *b1 = NULL;
    float *b2 = NULL;
    float *b3 = NULL;
    float *dEdA1_ave = NULL;
    float *dEdA2_ave = NULL;
    float *dEdA3_ave = NULL;
    float *dEdb1_ave = NULL;
    float *dEdb2_ave = NULL;
    float *dEdb3_ave = NULL;
    float *dEdA1 = NULL;
    float *dEdA2 = NULL;
    float *dEdA3 = NULL;
    float *dEdb1 = NULL;
    float *dEdb2 = NULL;
    float *dEdb3 = NULL;

    int select;
    printf("NN inference for charactures.\n");
    printf("3 layer: \n");
    printf("    learning:       type 1\n");
    printf("    correct rate:   type 2\n");
    printf("    infer bmp file: type 3\n");
    printf("6 layer: \n");
    printf("    learning:       type 4\n");
    printf("    correct rate:   type 5\n");
    printf("    infer bmp file: type 6\n");
    printf("Quit: \n");
    printf("    type another");
    printf(" > ");
    scanf("%d", &select);

    switch (select) {
    case 1:
        A = malloc(sizeof(float) * 10 * 784);
        b = malloc(sizeof(float) * 10);
        rand_init(10 * 784, A);
        rand_init(10, b);

        index = malloc(sizeof(int) * train_count);
        rep(i, train_count) {
            index[i] = i;
        }

        dEdA_ave = malloc(sizeof(float) * 10 * 784);
        dEdb_ave = malloc(sizeof(float) * 10);
        y = malloc(sizeof(float) * 10);
        dEdA = malloc(sizeof(float) * 784 * 10);
        dEdb = malloc(sizeof(float) * 10);

        rep(i, epoch) {
            // train
            printf("epoch: %d\n", i + 1);
            printf("    now training...\n");
            shuffle(train_count, index);
            rep(j, train_count / mini_batch) {
                init(10 * 784, 0.0, dEdA_ave);
                init(10, 0.0, dEdb_ave);
            rep(k, mini_batch) {
                    backward3(A, b, train_x + 784 * index[j * mini_batch + k], train_y[index[j * mini_batch + k]], y, dEdA, dEdb);
                    add(10 * 784, dEdA, dEdA_ave);
                    add(10, dEdb, dEdb_ave);
                }
                scale(784 * 10, coefficient, dEdA_ave);
                scale(10, coefficient, dEdb_ave);
                add(784 * 10, dEdA_ave, A);
                add(10, dEdb_ave, b);
            }
            // test
            printf("    now testing...\n");
            sum = 0;
            error = 0.0;
            rep(i, test_count) {
            if (inference3(A, b, test_x + i * width * height, y) == test_y[i]) {
                    ++sum;
                }
                error += cross_entoropy_error(y, test_y[i]);
            }
            printf("        correct answer: %f%%\n", sum * 100.0 / test_count);
            printf("        cross entropy : %f\n", error * 100.0 / test_count);
        }
        printf("Save?(1/0) > ");
        scanf("%d", &input);
        switch (input) {
        case 1:
            printf("Filename > ");
            scanf("%s", filename);
            save(filename, 10, 784, A, b);
            break;
        case 0:
        default:
            printf("End learning...");
            break;
        }
        free(A);
        free(b);
        free(index);
        free(dEdA_ave);
        free(dEdb_ave);
        free(y);
        free(dEdA);
        free(dEdb);
        break;

    case 2:
        printf("Filename  > ");
        scanf("%s", filename);
        A = malloc(sizeof(float) * 10 * 784);
        b = malloc(sizeof(float) * 10);
        load(filename, 10, 784, A, b);
        sum = 0;
        y = malloc(sizeof(float) * 10);
        rep(i, test_count) {
            if (inference3(A, b, test_x + i * width * height, y) == test_y[i]) {
                ++sum;
            }
        }
        free(y);
        printf("%f%%\n", sum * 100.0 / test_count);
        free(A);
        free(b);
        break;

    case 3:
        printf("parameters' filename  > ");
        scanf("%s", filename);
        A = malloc(sizeof(float) * 10 * 784);
        b = malloc(sizeof(float) * 10);
        y = malloc(sizeof(float) * 10);
        load(filename, 10, 784, A, b);
        printf("bmpfile name  > ");
        scanf("%s", filename);
        x = load_mnist_bmp(filename);
        printf("%d\n", inference3(A, b, x, y));
        free(A);
        free(b);
        free(y);
        free(x);
        break;

    case 4:
        A1 = malloc(sizeof(float) * 50 * 784);
        A2 = malloc(sizeof(float) * 100 * 50);
        A3 = malloc(sizeof(float) * 10 * 100);
        b1 = malloc(sizeof(float) * 50);
        b2 = malloc(sizeof(float) * 100);
        b3 = malloc(sizeof(float) * 10);
        rand_init(50 * 784, A1);
        rand_init(100 * 50, A2);
        rand_init(10 * 100, A3);
        rand_init(50, b1);
        rand_init(100, b2);
        rand_init(10, b3);

        index = malloc(sizeof(int) * train_count);
        rep(i, train_count) {
            index[i] = i;
        }

        dEdA1_ave = malloc(sizeof(float) * 50 * 784);
        dEdA2_ave = malloc(sizeof(float) * 100 * 50);
        dEdA3_ave = malloc(sizeof(float) * 10 * 100);
        dEdb1_ave = malloc(sizeof(float) * 50);
        dEdb2_ave = malloc(sizeof(float) * 100);
        dEdb3_ave = malloc(sizeof(float) * 10);
        y = malloc(sizeof(float) * 10);
        dEdA1 = malloc(sizeof(float) * 50 * 784);
        dEdA2 = malloc(sizeof(float) * 100 * 50);
        dEdA3 = malloc(sizeof(float) * 10 * 100);
        dEdb1 = malloc(sizeof(float) * 50);
        dEdb2 = malloc(sizeof(float) * 100);
        dEdb3 = malloc(sizeof(float) * 10);

        rep(i, epoch) {
            // train
            printf("epoch: %d\n", i + 1);
            printf("	now training...\n");
            shuffle(train_count, index);
            rep(j, train_count / mini_batch) {
                init(50 * 784, 0.0, dEdA1_ave);
                init(100 * 50, 0.0, dEdA2_ave);
                init(10 * 100, 0.0, dEdA3_ave);
                init(50, 0.0, dEdb1_ave);
                init(100, 0.0, dEdb2_ave);
                init(10, 0.0, dEdb3_ave);
                rep(k, mini_batch) {
                    backward6(A1, b1, A2, b2, A3, b3, train_x + 784 * index[j * mini_batch + k], train_y[index[j * mini_batch + k]], y, dEdA1, dEdb1, dEdA2, dEdb2, dEdA3, dEdb3);
                    add(50 * 784, dEdA1, dEdA1_ave);
                    add(100 * 50, dEdA2, dEdA2_ave);
                    add(10 * 100, dEdA3, dEdA3_ave);
                    add(50, dEdb1, dEdb1_ave);
                    add(100, dEdb2, dEdb2_ave);
                    add(10, dEdb3, dEdb3_ave);
                }
                scale(50 * 784, coefficient, dEdA1_ave);
                scale(100 * 50, coefficient, dEdA2_ave);
                scale(10 * 100, coefficient, dEdA3_ave);
                scale(50, coefficient, dEdb1_ave);
                scale(100, coefficient, dEdb2_ave);
                scale(10, coefficient, dEdb3_ave);
                add(50 * 784, dEdA1_ave, A1);
                add(100 * 50, dEdA2_ave, A2);
                add(10 * 100, dEdA3_ave, A3);
                add(50, dEdb1_ave, b1);
                add(100, dEdb2_ave, b2);
                add(10, dEdb3_ave, b3);
            }
            // test
            printf("	now testing...\n");
            sum = 0;
            error = 0.0;
            rep(i, test_count) {
                if (inference6(A1, b1, A2, b2, A3, b3, test_x + i * width * height, y) == test_y[i]) {
                    ++sum;
                }
                error += cross_entoropy_error(y, test_y[i]);
            }
            printf("		correct answer: %f%%\n", sum * 100.0 / test_count);
            printf("		cross entropy : %f\n", error * 100.0 / test_count);
        }

        printf("Save?(1/0) > ");
        scanf("%d", &input);
        switch (input) {
        case 1:
            printf("Filename1 > ");
            scanf("%s", filename);
            save(filename, 50, 784, A1, b1);
            printf("Filename2 > ");
            scanf("%s", filename);
            save(filename, 100, 50, A2, b2);
            printf("Filename3 > ");
            scanf("%s", filename);
            save(filename, 10, 100, A3, b3);
            break;
        case 0:
        default:
            printf("End learning...");
            break;
        }

        free(A1);
        free(A2);
        free(A3);
        free(b1);
        free(b2);
        free(b3);
        free(index);
        free(dEdA1_ave);
        free(dEdA2_ave);
        free(dEdA3_ave);
        free(dEdb1_ave);
        free(dEdb2_ave);
        free(dEdb3_ave);
        free(dEdA1);
        free(dEdA2);
        free(dEdA3);
        free(dEdb1);
        free(dEdb2);
        free(dEdb3);
        free(y);
        break;

    case 5:
        A1 = malloc(sizeof(float) * 50 * 784);
        A2 = malloc(sizeof(float) * 100 * 50);
        A3 = malloc(sizeof(float) * 10 * 100);
        b1 = malloc(sizeof(float) * 50);
        b2 = malloc(sizeof(float) * 100);
        b3 = malloc(sizeof(float) * 10);
        printf("Filename1  > ");
        scanf("%s", filename);
        load(filename, 50, 784, A1, b1);
        printf("Filename2  > ");
        scanf("%s", filename);
        load(filename, 50, 784, A2, b2);
        printf("Filename3  > ");
        scanf("%s", filename);
        load(filename, 50, 784, A3, b3);
        sum = 0;
        y = malloc(sizeof(float) * 10);
        rep(i, test_count) {
            if (inference6(A1, b1, A2, b2, A3, b3, test_x + i * width * height, y) == test_y[i]) {
                ++sum;
            }
        }
        free(y);
        printf("%f%%\n", sum * 100.0 / test_count);
        free(A1);
        free(A2);
        free(A3);
        free(b1);
        free(b2);
        free(b3);
        break;

    case 6:
        A1 = malloc(sizeof(float) * 50 * 784);
        A2 = malloc(sizeof(float) * 100 * 50);
        A3 = malloc(sizeof(float) * 10 * 100);
        b1 = malloc(sizeof(float) * 50);
        b2 = malloc(sizeof(float) * 100);
        b3 = malloc(sizeof(float) * 10);
        y = malloc(sizeof(float) * 10);
        printf("parameters' filename1 > ");
        scanf("%s", filename);
        load(filename, 50, 784, A1, b1);
        printf("parameters' filename2 > ");
        scanf("%s", filename);
        load(filename, 50, 784, A2, b2);
        printf("parameters' filename3 > ");
        scanf("%s", filename);
        load(filename, 50, 784, A3, b3);
        printf("bmp file name > ");
        scanf("%s", filename);
        x = load_mnist_bmp(filename);
        printf("%d\n", inference6(A1, b1, A2, b2, A3, b3, x, y));
        free(A1);
        free(A2);
        free(A3);
        free(b1);
        free(b2);
        free(b3);
        free(y);
        free(x);
        break;

    default:
        break;
    }
    return 0;
}

// inline static void print(int m, int n, const float *x) {
//     int i, j;
//     for (i = 0; i < m; ++i) {
//         for (j = 0; j < n; ++j) {
//             printf("%.4f ", x[i * n + j]);
//         }
//         printf("\n");
//     }
// }

// inline static void print_int(int m, int n, const int *x) {
//     int i, j;
//     for (i = 0; i < m; ++i) {
//         for (j = 0; j < n; ++j) {
//             printf("%d ", x[i * n + j]);
//         }
//         printf("\n");
//     }
// }

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
    float *y_tmp = malloc(sizeof(float) * 10);
    // A: 10x784, b: 10, x: 784
    fc(10, 784, x, A, b, y_tmp);
    relu(10, y_tmp, y_tmp);
    softmax(10, y_tmp, y);
    int max = (int)max_index(10, y);
    free(y_tmp);
    return max;
}

inline static void softmaxwithloss_bwd(int n, const float *y, unsigned char t, float *dEdx) {
    copy(n, y, dEdx);
    dEdx[t] -= 1.0;
}

inline static void relu_bwd(int n, const float *x, const float *dEdy, float *dEdx) {
    rep(i, n) {
        dEdx[i] = (x[i] > 0.0) ? dEdy[i] : 0.0;
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
    float *relu_x = malloc(sizeof(float) * 10);
    float *y_tmp = malloc(sizeof(float) * 10);
    fc(10, 784, x, A, b, relu_x);
    relu(10, relu_x, y_tmp);
    softmax(10, y_tmp, y);

    float *dEdx_tmp = malloc(sizeof(float) * 10);
    softmaxwithloss_bwd(10, y, t, dEdx_tmp);
    relu_bwd(10, relu_x, dEdx_tmp, dEdx_tmp);
    float *dEdx = malloc(sizeof(float) * 784);
    fc_bwd(10, 784, x, dEdx_tmp, A, dEdA, dEdb, dEdx);
    free(relu_x);
    free(y_tmp);
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
    rep(i, n) {
        o[i] += x[i];
    }
}

inline static void scale(int n, float x, float *o) {
    rep(i, n) {
        o[i] *= x;
    }
}

inline static void init(int n, float x, float *o) {
    rep(i, n) {
        o[i] = x;
    }
}

inline static void rand_init(int n, float *o) {
    rep(i, n) {
        o[i] = (float)rand() / RAND_MAX * 2.0 - 1.0;
    }
}

inline static int inference6(const float *A1, const float *b1, const float *A2, const float *b2, const float *A3, const float *b3, const float *x, float *y) {
    // A1: 50x784, b1: 50, x: 784
    // A2: 100x50, b2: 100,
    // A3: 10x100, b3: 10,
    float *y1 = malloc(sizeof(float) * 50);
    float *y2 = malloc(sizeof(float) * 100);
    float *y3 = malloc(sizeof(float) * 10);
    fc(50, 784, x, A1, b1, y1);
    relu(50, y1, y1);
    fc(100, 50, y1, A2, b2, y2);
    relu(100, y2, y2);
    fc(10, 100, y2, A3, b3, y3);
    softmax(10, y3, y);
    int max = (int)max_index(10, y);
    free(y1);
    free(y2);
    free(y3);
    return max;
}

inline static void backward6(const float *A1, const float *b1, const float *A2, const float *b2, const float *A3, const float *b3, const float *x, unsigned char t, float *y, float *dEdA1, float *dEdb1, float *dEdA2, float *dEdb2, float *dEdA3, float *dEdb3) {
    // A1: 50x784, b1: 50, x: 784
    // A2: 100x50, b2: 100,
    // A3: 10x100, b3: 10,

    float *y1 = malloc(sizeof(float) * 50); // fc2's input
    float *y2 = malloc(sizeof(float) * 100); // fc3's input
    float *y3 = malloc(sizeof(float) * 10);
    float *relu_x1 = malloc(sizeof(float) * 50); 
    float *relu_x2 = malloc(sizeof(float) * 100); 
	
    fc(50, 784, x, A1, b1, relu_x1);
    relu(50, relu_x1, y1);
    fc(100, 50, y1, A2, b2, relu_x2);
    relu(100, relu_x2, y2);
    fc(10, 100, y2, A3, b3, y3);
    softmax(10, y3, y);

    float *dEdx_sm = malloc(sizeof(float) * 10);
    float *dEdx_fc3 = malloc(sizeof(float) * 100);
    float *dEdx_fc2 = malloc(sizeof(float) * 50);
    float *dEdx = malloc(sizeof(float) * 784);

    softmaxwithloss_bwd(10, y, t, dEdx_sm);
    fc_bwd(10, 100, y2, dEdx_sm, A3, dEdA3, dEdb3, dEdx_fc3);
    relu_bwd(100, relu_x2, dEdx_fc3, dEdx_fc3);
    fc_bwd(100, 50, y1, dEdx_fc3, A2, dEdA2, dEdb2, dEdx_fc2);
    relu_bwd(50, relu_x1, dEdx_fc2, dEdx_fc2);
    fc_bwd(50, 784, x, dEdx_fc2, A1, dEdA1, dEdb1, dEdx);

    free(y1);
    free(y2);
    free(y3);
    free(relu_x1);
    free(relu_x2);
    free(dEdx_sm);
    free(dEdx_fc3);
    free(dEdx_fc2);
    free(dEdx);
}

inline static void save(const char *filename, int m, int n, const float *A, const float *b) {
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

inline static void load(const char *filename, int m, int n, float *A, float *b) {
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
