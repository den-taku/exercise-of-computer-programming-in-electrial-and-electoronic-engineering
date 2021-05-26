#include <stdio.h>

int main() {
    signed int i = 5;

    while(i >= 0) {
        printf("i=%d\n", i);
        i = i - 1;
    }

    return 0;
}