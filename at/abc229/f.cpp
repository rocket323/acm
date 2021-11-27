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

int n, a[maxl], b[maxl];
ll f[maxl][2], g[maxl][2];

int main() {
    scanf("%d", &n);
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum = sum + a[i];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        sum = sum + b[i];
    }

    for (int i = 0; i <= n; i++) {
        f[i][0] = f[i][1] = -inf;
        g[i][0] = g[i][1] = -inf;
    }
    f[1][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (f[i][j] < 0)
                continue;

            for (int k = 0; k < 2; k++) {
                f[i+1][k] = max(f[i+1][k], f[i][j] + a[i+1] * k + b[i] * (j != k));
            }
        }
    }
    ll ans1 = max({ f[n][0], f[n][1] + b[n] });

    g[1][1] = a[1];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (g[i][j] < 0)
                continue;

            for (int k = 0; k < 2; k++) {
                g[i+1][k] = max(g[i+1][k], g[i][j] + a[i+1] * k + b[i] * (j != k));
            }
        }
    }
    ll ans2 = max({ g[n][0] + b[n], g[n][1] });
    cout << sum - max(ans1, ans2) << endl;

    return 0;
}

