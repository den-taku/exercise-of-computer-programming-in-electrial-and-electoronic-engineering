#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 0 -> 1, 2 -> 2, 5 -> 3
int encode(int n);
// 1 -> 0, 2 -> 2, 3 -> 5
int decode(int n);

void print_result(int cpu, int plr);

int main(void) {
    int plr = -1;
    int cpu = -1;
    srand(time(NULL));
    do {
        printf("Your input (0,2,5): ");
        scanf("%d", &plr);
        if(!(plr == 0 || plr == 2 || plr == 5)) {
            printf("Invalid input => Input again.\n");
            goto contin;
        }
        plr = encode(plr);
        cpu = rand() % 3 + 1;
        printf("Comp:%d vs You:%d", decode(cpu), decode(plr));
        print_result(cpu, plr);
        if (plr != cpu) {
            break;
        }
        contin: ;
    } while(1);

    return 0;
}

int encode(int n) {
    return (n + 2) / 2;
}

int decode(int n) {
    return (n-1)*(n-1)+1*(n/2);
}

void print_result(int cpu, int plr) {
    if (cpu == plr) {
        printf(" => Try again.\n");
    } else if ((cpu + 1) % 3 == plr) {
        printf(" => You lose.\n");
    } else {
        printf(" => You win.\n");
    }
}