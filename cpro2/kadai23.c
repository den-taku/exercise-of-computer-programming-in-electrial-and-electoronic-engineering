#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, d;

    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);

    d = b * b - 4.0 * a * c;

    if (d > 0) {
        double answer_p = (-b + sqrt(d)) / (2.0 * a);
        double answer_n = (-b - sqrt(d)) / (2.0 * a);
        printf("%.6f\n%.6f\n", answer_p, answer_n);
    } else if (d == 0) {
        double answer = (-b + sqrt(d)) / (2.0 * a);
        printf("%.6f(multiple root)\n", answer);
    } else {
        double answer_r = -b / (2.0 * a);
        double answer_i = sqrt(-d) / (2.0 * a);
        printf("%.6f + %.6f i\n%.6f - %.6f i\n", answer_r, answer_i, answer_r, answer_i);
    }

    return 0;
}