#include <stdio.h>

void copy_file(FILE *fp_r, FILE *fp_w);

int main() {
	FILE *fp_r, *fp_w;
	fp_r = fopen("test.txt", "r");
	if (!fp_r) {
		printf("test.txt cannot open.");
		return 1;
	}
	fp_w = fopen("copy.txt", "w");
	if (!fp_w) {
		printf("copy.txt cannot open");
		return 1;
	}
	copy_file(fp_r, fp_w);
	fclose(fp_r);
	fclose(fp_w);
	return 0;
}

void copy_file(FILE *fp_r, FILE *fp_w) {
	char buffer[256];
	while (fgets(buffer, 256, fp_r)) {
		fputs(buffer, fp_w);
	}
}