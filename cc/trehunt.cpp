#include <stdio.h>
#include <cstring>

using ll = long long;
const int maxl = 2e7 + 10;
const int mod = 998244353;

int t, n, m;
int a[maxl + 10], d[maxl + 10], dd[maxl + 10];
int f[maxl];

void add(int l, int r, int a0, int D) {
    d[l] = (d[l] + a0) % mod;
    if (l < r) {
        dd[l + 1] = (dd[l + 1] + D) % mod;
        dd[r + 1] = (dd[r + 1] + mod - D % mod) % mod;
    }
    int x = ((ll)a0 + (ll)D * (r - l)) % mod;
    d[r + 1] = (d[r + 1] + mod - x % mod) % mod;
}

void sumup() {
    for (int i = 1; i < maxl; i++) {
        dd[i] = (dd[i] + dd[i - 1]) % mod;
        d[i] = (d[i] + dd[i]) % mod;
    }

    for (int i = 1; i < maxl; i++) {
        d[i] = (d[i] + d[i - 1]) % mod;
        a[i] = (a[i] + d[i]) % mod;
    }
}

int main() {
    scanf("%d", &t);

    f[0] = 1;
    for (int i = 1; i < maxl; i++) {
        f[i] = (ll)f[i - 1] * 31 % mod;
    }

    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n + m; i++) {
            a[i] = d[i] = dd[i] = 0;
        }
        for (int i = 1; i < n; i++) {
            a[i] = (a[i] + (ll)(n - i) * m % mod) % mod;
            if (m > 1) {
                add(i + 1, i + m - 1, (ll)2 * (n - i) * (m - 1) % mod, mod - 2 * (n - i) % mod);
            }
        }

        for (int i = 1; i < m; i++) {
            a[i] = (a[i] + (ll)n * (m - i) % mod) % mod;
        }

        sumup();

        int ans = 0;
        for (int i = 1; i <= n + m - 2; i++) {
            int x = (ll)a[i] * f[i - 1] % mod;
            ans = (ans + x) % mod;
        }
        printf("%d\n", ans);
    }

    return 0;
}
