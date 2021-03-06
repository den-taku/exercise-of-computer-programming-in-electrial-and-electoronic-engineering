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
    srand((unsigned)time(NULL));
    int i;
    for(i = 0; i < 10; ++i) {
        a[i] = 0;
    }
    for(i = 0; i < n; ++ i) {
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

// n =      10:  10.0  30.0   0.0  10.0  20.0  10.0   0.0  10.0   0.0  10.0 
// n =     100:  13.0  11.0   7.0   8.0  11.0   8.0   7.0  14.0   9.0  12.0 
// n =    1000:   9.9   9.2   8.6   9.3   9.6  12.5  10.0  11.3   9.2  10.4 
// n =   10000:  10.3  10.4   9.3   9.8  10.1  10.0  10.2  10.5   9.9   9.4 
// n =  100000:   9.9  10.2   9.9  10.0  10.1   9.9  10.0  10.1   9.9   9.9 
// n = 1000000:  10.0  10.0  10.0  10.0  10.1   9.9  10.1  10.0  10.0  10.0