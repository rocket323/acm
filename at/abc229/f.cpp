#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <unordered_set>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, m, a[maxl], b[maxl];
ll f[maxl][2], g[maxl][2];

int main() {
    scanf("%d", &n);
    m = 0;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        sum += b[i];
    }

    memset(f, 0, sizeof f);
    f[1][0] = 0;
    f[1][1] = 0;
    for (int i = 2; i <= n; i++) {
        f[i][0] = max({ f[i-1][0] + b[i-1], f[i-1][1] + b[i-1] });
        f[i][1] = max({ f[i-1][0] + b[i-1] + a[i], f[i-1][1] + a[i] });
    }
    ll ans1 = max({ f[n][0] + b[n], f[n][1] + b[n] });

    memset(g, 0, sizeof g);
    g[1][0] = 0;
    g[1][1] = a[1];
    for (int i = 2; i <= n; i++) {
        g[i][0] = max({ g[i-1][0] + b[i-1], g[i-1][1] + b[i-1] });
        g[i][1] = max({ g[i-1][0] + b[i-1] + a[i], g[i-1][1] + a[i] });
    }
    ll ans2 = max({ g[n][0] + b[n], g[n][1] });
    cout << sum - max(ans1, ans2) << endl;

    return 0;
}

