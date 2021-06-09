#include <stdio.h>

int main() {
    char str[] = "Sun";
    int n[] = {10, 20, 40};
    double m[] = {1.5, 3.5, 7.5};
    printf("value: %c, address: %p\nvalue: %d, address: %p\nvalue: %f, address: %p\n", str[0], &str[0], n[0], &n[0], m[0], &m[0]);
    printf("value: %c, address: %p\nvalue: %d, address: %p\nvalue: %f, address: %p\n", str[1], &str[1], n[1], &n[1], m[1], &m[1]);
    printf("value: %c, address: %p\nvalue: %d, address: %p\nvalue: %f, address: %p\n", str[2], &str[2], n[2], &n[2], m[2], &m[2]);
    return 0;
}