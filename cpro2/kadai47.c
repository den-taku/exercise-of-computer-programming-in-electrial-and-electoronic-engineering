#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hist(int n);
void display(int size);

int a[10] = {0};

int main() {
    hist(10);
    hist(100);
    hist(1000);
    hist(10000);
    hist(100000);
    hist(1000000);
    return 0;
}

void hist(int n) {
    int i;
    for(i = 0; i < 10; ++i) {
        a[i] = 0;
    }
    for(i = 0; i < n; ++ i) {
        srand((unsigned)time(NULL));
        ++a[rand() % 10];
    }
    display(n);
}

void display(int size) {
    int i;
    printf("n = %7d: ", size);
    for(i = 0; i < 10; ++i) {
        printf(" %4.1f ", ((float) a[i]) / ((float) size) * 100.0);
    }
    printf("\n");
}

// n =      10:   0.0   0.0   0.0   0.0   0.0   0.0  100.0   0.0   0.0   0.0 
// n =     100:   0.0   0.0   0.0   0.0   0.0   0.0  100.0   0.0   0.0   0.0 
// n =    1000:   0.0   0.0   0.0   0.0   0.0   0.0  100.0   0.0   0.0   0.0 
// n =   10000:   0.0   0.0   0.0   0.0   0.0   0.0  100.0   0.0   0.0   0.0 
// n =  100000:   0.0   0.0   0.0   0.0   0.0   0.0  100.0   0.0   0.0   0.0 
// n = 1000000:   0.0   0.0   0.0   0.0   0.0   0.0  100.0   0.0   0.0   0.0 