#include <stdio.h>
#include <math.h>

int main() {
    double a;
    double b;
    double c;
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);
    double answer_p = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    double answer_n = (-b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
    printf("%.6f\n%.6f\n", answer_p, answer_n);
    return 0;
}