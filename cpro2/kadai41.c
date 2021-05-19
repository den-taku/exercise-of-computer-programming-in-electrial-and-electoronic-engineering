#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b);

int main() {
    int x[5] = {4, 1, 8, 2, 9};
    int i;
    int range;

    for(i = 0; i < 5; ++i) {
        printf("x[%d] = %d\n", i, x[i]);
    }

    qsort(x, sizeof(x) / sizeof(x[0]), sizeof(int), cmp);
    range = x[0];

    printf("max = %d\n", range);
    return 0;

}

int cmp(const void* a, const void* b) {
    int A = *(int*)a;
    int B = *(int*)b;
    return B - A;
}