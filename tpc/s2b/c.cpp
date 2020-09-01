#include <bits/stdc++.h>

const int maxl = 1e5 + 10;

int t, a[maxl];
int n;

bool check(int a, int b) {
    if (a % b == 0 || b % a == 0)
        return true;
    else
        return false;
}

bool solve() {
    for (int i = 2; i <= n; i++) {
        if (!check(a[i], a[i - 1]))
            return false;
    }

    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        puts(solve() ? "Yes" : "No");
    }

    return 0;
}
