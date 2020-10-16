#include <bits/stdc++.h>
#define ll long long

int n, m, a[100][100];
long long f[100][100], t[100];

long long solve(int a[]) {
    memset(f, 0, sizeof f);
    f[0][0] = 0;

    for (int c = 0; c < m; c++) {
        for (int l = 0; l <= c; l++) {
            int num1 = a[l + 1], num2 = a[m - (c - l)];
            f[c + 1][l + 1] = std::max(f[c + 1][l + 1], f[c][l] + num1 * t[c + 1]);
            f[c + 1][l] = std::max(f[c + 1][l], f[c][l] + num2 * t[c + 1]);
        }
    }

    ll ans = 0;
    for (int l = 0; l <= m; l++)
        ans = std::max(ans, f[m][l]);
    return ans;
}

int main() {
    t[0] = 1;
    for (int i = 1; i < 100; i++)
        t[i] = t[i - 1] * 2;

    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }

        long long ans = 0;
        for (int r = 1; r <= n; r++) {
            ans += solve(a[r]);
        }
        printf("%d\n", ans);
    }

    return 0;
}
