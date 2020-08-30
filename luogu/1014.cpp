#include <bits/stdc++.h>

int n;

void solve(int n) {
    int i = 1;
    for (i = 1; i <= n; i++) {
        if (i >= n) {
            break;
        } else {
            n -= i;
        }
    }

    int a = n;
    int b = (i + 1) - a;

    if (i & 1) {
        std::swap(a, b);
    }

    printf("%d/%d\n", a, b);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        solve(n);
    }

    return 0;
}
