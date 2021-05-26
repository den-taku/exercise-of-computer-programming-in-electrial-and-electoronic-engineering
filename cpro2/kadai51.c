#include <stdio.h>

int combination(int n, int r);

int main(void) {
    int n, r;
    printf("n = ");
    scanf("%d", &n);
    printf("r = ");
    scanf("%d", &r);
    printf("%dC%d = %d\n", n, r, combination(n, r));
}

int combination(int n, int r) {
    if (n == r || r == 0) {
        return 1;
    } else if (r == 1) {
        return n;
    } else {
        return combination(n - 1, r - 1) + combination(n - 1, r);
    }
}