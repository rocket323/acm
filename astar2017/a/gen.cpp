#include <stdio.h>

int main() {
    int n = 100000;
    printf("%d\n", n);
    for (int i = 1; i < n; ++i) {
        // printf("%d %d %c\n", i, i + 1, i < n / 2 ? '0' : '1');
        printf("%d %d 0\n", i, i + 1);
    }
    printf("%d %d 1\n", 1, 2);

    return 0;
}

