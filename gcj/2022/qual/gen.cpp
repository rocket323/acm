#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxl = 1e5;

void gen1() {
    int n = maxl;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("1 ");
    puts("");
    for (int i = 1; i <= n; i++)
        printf("0 ");
    puts("");
}

void gen2() {
    int n = maxl;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("1 ");
    puts("");
    for (int i = 1; i <= n; i++)
        printf("%d ", i - 1);
    puts("");
}

void gen3() {
    int n = maxl;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("1 ");
    puts("");
    for (int i = 1; i <= n; i++)
        printf("%d ", i / 2);
    puts("");
}

int main() {
    printf("3\n");
    gen1();
    gen2();
    gen3();
    return 0;
}