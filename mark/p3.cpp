#include <bits/stdc++.h>

const int maxl = 1e5 + 10;
int n, c[1010], t, a;

int calc(int x) {
    for (int i = 1; i < x; i++) {
        if (c[i] == 0 && c[x - i] == 0 && i != x - i)
            return 1;
    }
    return 0;
}

int solve() {
    int c2 = 0, x = 0, ans = 0;
    for (int i = 1; i <= 1000; i++) {
        if (c[i] > 2)
            return 0;
        else if (c[i] == 2) {
            c2++;
            x = i;
        }
    }
    if (c2 > 1) {
        return 0;
    } else if (c2 == 1) {
        ans += 2 * calc(x);
    } else {
        for (int i = 1; i <= 1000; i++) {
            if (c[i]) {
                ans += calc(i);
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int a;
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            c[a]++;
        }

        printf("%d\n", solve());
    }

    return 0;
}
