#include <stdio.h>
#include <cstring>

using ll = long long;
const int maxl = 2e7 + 10;
const int mod = 998244353;

int t, n, m;
int a[maxl + 10], d[maxl + 10], dd[maxl + 10];
int f[maxl];

void add_dd(int l, int x) {
    dd[l] = (dd[l] + x) % mod;
}

void add_d(int l, int x) {
    d[l] = (d[l] + x) % mod;
}

void add_d(int l, int r, int x) {
    add_dd(l, x);
    add_dd(r + 1, mod - x % mod);
}

void add(int l, int r, int a0, int d) {
    add_d(l, a0);
    if (l < r) {
        add_d(l + 1, r, d);
    }
    int x = ((ll)a0 + (ll)d * (r - l)) % mod;
    add_d(r + 1, mod - x % mod);
}

void add(int l, int x) {
    a[l] = (a[l] + x) % mod;
}

void out(int a[]) {
    for (int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    puts("");
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
        memset(a, 0, sizeof(a));
        memset(d, 0, sizeof(d));
        memset(dd, 0, sizeof(dd));

        for (int i = 1; i < n; i++) {
            add(i + 0, i + m - 1, (ll)2 * (n - i) * m % mod, mod - 2 * (n - i) % mod);
        }

        for (int i = 1; i < m; i++) {
            add(i, (ll)n * (m - i) % mod);
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
