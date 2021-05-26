#include <stdio.h>
#include <math.h>

int main() {
    double answer1 = (-10e+15 + sqrt(10e+15 * 10e+15 - 4.0 * 10e+14)) / 2.0;
    double answer2 = 2.0 * 10e+14 / (-10e+15 - sqrt(10e+15 * 10e+15 - 4.0 * 10e+14));
    printf("fst: %f\n", answer1);
    printf("scd: %f\n", answer2);
}