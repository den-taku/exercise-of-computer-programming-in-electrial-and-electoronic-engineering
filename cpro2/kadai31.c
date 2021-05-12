#include <stdio.h>

// int fact(int n);
// int fact_inner(int n, int buffer);

int main(void) {
    int n = 0;
    printf("input number, then calculate factorial: ");
    scanf("%d", &n);
    int fact = 1;
    int tmp = n;
    if (tmp == 0) {
        tmp = 1;
    } else {
       for(; tmp > 0;) {
           fact *= tmp;
           --tmp;
       } 
    }
    printf("%d! = %d\n", n, fact);
    return 0;
}

// int fact(int n) {
//     return fact_inner(n, 1);
// }

// // for tail call optimization
// int fact_inner(int n, int buffer) {
//     if (n == 0) {
//         return buffer;
//     } else if (n > 0) {
//         return fact_inner(n-1, buffer*n);
//     } else {
//         return -1;
//     }
// }