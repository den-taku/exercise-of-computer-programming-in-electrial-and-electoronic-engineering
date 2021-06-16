#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <stdio.h>

void bubble_sort(int *array, int n);
void print_array(int *array, int n, int index);
void swap(int *x, int *y);

int main() {
	int a[256];
	int n;
	printf("N: ");
	scanf("%d", &n);
	printf("Data: ");
	rep (i, n) {
		scanf("%d", &a[i]);
	}
	bubble_sort(a, n);
}

void bubble_sort(int *array, int n) {
	rep (i, n) {
		for (int j = n - 1; j >= i + 1; --j) {
			if (array[j] < array[j-1]) {
				swap(&array[j], &array[j - 1]);
			}
		}
		print_array(array, n, i);
	}
}

void print_array(int *array, int n, int i) {
	printf("loop%d: ", i);
	rep (i, n) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}