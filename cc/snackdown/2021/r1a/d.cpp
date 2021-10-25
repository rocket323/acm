#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 2e9 + 10;
const int maxl = 1e5 + 10;

int t, n, a[maxl], b[maxl], top;
ll ans;
ll f[maxl], g[maxl], m;

ll gao(int i, int j) {
    if (j == i || j <= 0 || j > n - 1 || j > i + 1)
        return inf;

    if (i == 0 || j == n - 1)
        return inf;

    int x = a[i] - a[0];
    int y = a[n - 1] - a[j];
    return abs(x - y);
}

ll gao2(int a[], int n) {
    for (int i = 0; i <= n; i++) {
        f[i] = g[i] = 0;
    }
    f[0] = a[0];
    for (int i = 1; i < n; i++)
        f[i] = f[i-1] + a[i];

    g[n] = 0;
    for (int i = n-1; i >= 0; i--)
        g[i] = g[i+1] + a[i];

    ll ans = inf;
    for (int i = 0; i < n; i++) {
        ll tmp = 0;
        if (i > 0) {
            tmp += (ll)a[i] * i - f[i-1];
        }
        if (i < n-1) {
            tmp += g[i+1] - (ll)a[i] * (n - 1 - i);
        }
        ans = min(ans, tmp);
    }
    // printf("x %lld\n", ans);
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        top = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }
        sort(b, b + n);
        m = n;
        for (int i = 0; i < n; i++) {
            if (top - 4 >= 0 && a[top - 4] == b[i])
                continue;
            a[top++] = b[i];
        }
        n = top;
        ans = 2e9 + 10;
        for (int i = 0; i < n-1; i++) {
            int d = a[i] - a[0];
            int x = a[n - 1] - d;
            int j = lower_bound(a, a + n, x) - a;
            for (int k = j-20; k <= j+20; k++) {
                ans = min(ans, gao(i, k));
            }
            for (int k = i+20; k >= i-20; k--) {
                ans = min(ans, gao(i, k));
            }
        }
        ans = min(ans, gao2(b, m - 1));
        ans = min(ans, gao2(b + 1, m - 1));
        cout << ans << endl;
    }
    return 0;
}

