#include <stdio.h>

int input();
int fact(int n);
int fact_for_tail_call_optimization(int n, int buffer);
int perm(int n, int r);

int main() {
    int n, r;
    n = input();
    for(r = 0; r <= n; ++r) {
        printf("P(%d, %d) = %d\n", n, r, perm(n, r));
    }
}

int input() {
    int buffer, count;
    do {
        printf("n = ");
        count = scanf("%d", &buffer);
        if (count != 1) {
            printf("Invalid input\n");
            scanf("%*s");
            printf("");
        } else if (buffer < 0) { 
            printf("Invalid input\n");
        }else {
            break;
        }
    } while (1);
    return buffer;
}

int fact(int n) {
    return fact_for_tail_call_optimization(n, 1);
}

int fact_for_tail_call_optimization(int n, int buffer) {
    if (n == 0) {
        return buffer;
    } else if (n > 0) {
        return fact_for_tail_call_optimization(n - 1, buffer * n);
    } else {
        return -1;
    }
}

int perm(int n, int r) {
    int denominator = fact(n);
    int numerator = fact(n - r);
    return denominator / numerator;
}