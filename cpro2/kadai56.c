#include <stdio.h>

int main() {
    float x = 1;
    int i;
    for (i = 0; i < 10; i++) {
        x = x - 1.0 / 3.0;
        if (x < 0.0001) {
            break;
        }
        printf("%f\n", x);
    }
    return 0;
}