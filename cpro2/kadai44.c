#include <stdio.h>

#define M 3
#define N 4

int a[M][N];

void input();
void display();

int main() {
    input();
    display();
    return 0;
}

void input() {
    int i, j;

    for(i = 0; i < M; ++i) {
        for(j = 0; j < N; ++j) {
            a[i][j] = 10 * i + j;
        }
    }
}

void display() {
    int i, j;

    for(i = 0; i < M; ++i) {
        for(j = 0; j < N; ++j) {
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
}