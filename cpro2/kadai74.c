#include <stdio.h>

void minmax(int data[], int *min, int *max);

int main() {
    int d[3] = {0};
    int max, min;
    printf("input 1st integer : ");
    scanf("%d", &d[0]);
    printf("input 2nd integer : ");
    scanf("%d", &d[1]);
    printf("input 3rd integer : ");
    scanf("%d", &d[2]);
    minmax(d, &min, &max);
    printf("\nmin: %d, max: %d\n", min, max);
    return 0;
}

void minmax(int data[], int *min, int *max) {
    int i;
    *min = data[0];
    *max = data[0];
    for (i = 1; i < 3; ++i) {
        if (data[i] > *max) {
            *max = data[i];
        }
        if (data[i] < *min) {
            *min = data[i];
        }
    }
}