#include <stdio.h>

int main() {
    float a = 0, b = 0;
    double c = 0, d = 0;
    for (int i = 0; i < 1e+8; ++i) {
        a += 1e-8;
        c += 1e-8;
    }
    b = (1e-8) * (1e+8);
    d = (1e-8) * (1e+8);
    printf("a = %.20f\n", a);
    printf("b = %.20f\n", b);
    printf("c = %.20f\n", c);
    printf("d = %.20f\n", d);
}