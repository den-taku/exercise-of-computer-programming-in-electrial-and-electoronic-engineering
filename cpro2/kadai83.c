#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <stdio.h>
#include <math.h>

typedef struct {
	double x;
	double y;
} Vector2d;

double GetLength(Vector2d vec);
void ScaleVector(Vector2d *vec, double s);

int main() {
	Vector2d v;
	double s;
	printf("Input 2D Vector: ");
	scanf("%lf", &v.x);
	scanf("%lf", &v.y);
	printf("Input scale value: ");
	scanf("%lf", &s);
	ScaleVector(&v, s);
	printf("Result: %lf %lf\n", v.x, v.y);
	printf("Length: %lf\n", GetLength(v));
}

double GetLength(Vector2d vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void ScaleVector(Vector2d *vec, double s) {
	vec -> x *= s;
	vec -> y *= s;
}
