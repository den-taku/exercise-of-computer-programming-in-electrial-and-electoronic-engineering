#include <stdio.h>
void hoge(const int *a, int *b);

int main() {
	int a[] = {1, 2, 3, 4, 5};
	hoge(a, a);
	return 0;
}

void hoge(const int *a, int *b) {
	for (int i = 0; i < 5; ++i) {
		b[i] = a[(i + 2) % 5];
	}
	for (int i = 0; i < 5; ++i){
		printf("%d ", a[i]);
	}
	printf("\n");
	for (int i = 0; i < 5; ++i) {
		printf("%d ", b[i]);
	}
	printf("\n");
}