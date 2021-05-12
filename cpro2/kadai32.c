#include <stdio.h>

int main(void) {
    int n = 0;
    printf("input number, then calculate factorial: ");
    scanf("%d", &n);
    int fact = 1;
    int tmp = n;
    if (tmp == 0) {
        tmp = 1;
    }
    while(tmp > 0) {
        fact *= tmp;
        --tmp;
    }
    printf("%d! = %d\n", n, fact);
    return 0;
}