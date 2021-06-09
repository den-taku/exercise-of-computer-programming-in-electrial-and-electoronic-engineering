#include <stdio.h>

int main() {
    int len = 0;
    char str[128];
    printf("input a word: ");
    scanf("%s", str);
    while (str[len]) {
        if (97 <= str[len] && str[len] <= 122) {
            str[len] = ((str[len] - 97 + 1) % 26) + 97;
        } else if (65 <= str[len] && str[len] <= 90) {
            str[len] = ((str[len] - 65 + 1) % 26) + 65;
        }
        ++len;
    }
    printf("%s\n", str);
    return 0;
}