#include <stdio.h>

int main() {
    int in;
    printf("n = ");
    scanf("%d", &in);
    printf("n = ");
    for (int i = 0; i < 32; ++i) {
        printf("%d", (in & 0x80000000) >> 31);
        in = in << 1;
    }
    printf("\n");
}