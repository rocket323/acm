#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
const int mod = 998244353;
const int maxl = 3e5 + 10;

int n, a[maxl], c[maxl], b[maxl];
int top, f[maxl], g[maxl];

int lowbit(int x) {
    return x & -x;
}

void add(int n, int v) {
    n += 1;
    while (n < maxl) {
        c[n] = (c[n] + v) % mod;
        n += lowbit(n);
    }
}

int sum(int n) {
    n += 1;
    int ans = 0;
    while (n) {
        ans = (ans + c[n]) % mod;
        n -= lowbit(n);
    }
    return ans;
}

int pow(int a, int n) {
    int ans = 1, t = a;
    while (n) {
        if (n & 1) {
            ans = ((ll)ans * t) % mod;
        }
        t = ((ll)t * t) %mod;
        n >>= 1;
    }
    return ans;
}

int main() {
    int div = pow(2, mod - 2);
    f[0] = g[0] = 1;
    for (int i = 1; i < maxl; i++) {
        f[i] = (ll)f[i-1] * 2 % mod;
        g[i] = (ll)g[i-1] * div % mod;
    }

    scanf("%d", &n);
    top = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[top++] = a[i];
    }
    sort(b, b + top);
    top = unique(b, b + top) - b;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int d = lower_bound(b, b + top, a[i]) - b;
        int s = (ll)sum(d) * f[i-1] % mod;
        add(d, g[i]);
        ans = (ans + s) % mod;
    }
    printf("%d\n", ans);
    return 0;
}

