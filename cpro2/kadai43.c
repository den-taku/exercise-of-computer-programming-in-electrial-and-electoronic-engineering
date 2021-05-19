#include <stdio.h>
#include <stdlib.h>

float my_abs(float f);

int main() {
    float x = -1.3;
    float y = 3.7;
    float abs_x = my_abs(x);
    float abs_y = my_abs(y);
    printf("|x| = %f\n", abs_x);
    printf("|y| = %f\n", abs_y);
    return 0;
}

float my_abs(float f) {
    if (f >= 0) {
        return f;
    } else {
        return -f;
    }
}