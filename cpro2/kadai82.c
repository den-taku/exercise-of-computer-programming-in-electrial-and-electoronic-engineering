#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <stdio.h>
#include <math.h>

typedef struct {
	double x;
	double y;
} Vector2d;

double GetLength(Vector2d vec);

int main() {
	Vector2d v;
	printf("Input 2D Vector: ");
	scanf("%lf", &v.x);
	scanf("%lf", &v.y);
	printf("Length: %lf\n", GetLength(v));
}

double GetLength(Vector2d vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}