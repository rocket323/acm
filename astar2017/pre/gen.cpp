#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>

int main() {

    srand(time(0));
    int n = 100000;
    int m = 1000;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; ++i) {
        // printf("%d %d\n", 1000, 10);
        int a = rand() % 1000 + 1;
        int b = rand() % 11;
        printf("%d %d\n", a, b);
    }

    for (int i = 1; i <= m; ++i) {
        // printf("%d %d\n", 100000, 11);
        int k = rand() % 100001;
        int p = rand() % 1001;
        printf("%d %d\n", k, p);
    }

    return 0;
}

