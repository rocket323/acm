#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 5050;
const int mod = 1e9 + 7;

int t, n, k;
int a[maxl], cnt[105][105], C[maxl][maxl];
int f[maxl], g[maxl];

int main() {
    C[0][0] = 1;
    for (int i = 1; i < maxl; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = ((ll)C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }

    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        for (int i = 0; i <= n; i++) {
            f[i] = 0;
            g[i] = -1;
        }
        f[0] = 1;
        g[0] = 0;
        int l = 0;
        for (int i = 1; i <= n; i++) {
            int c = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (a[j] == a[i])
                    c++;
                if (g[j] == -1)
                    continue;

                int x = c - (a[j] == a[i]);
                if (x < k)
                    continue;

                int tmp = (ll)C[x - 1][k - 1] * f[j] % mod;
                if (g[j] + 1 > g[i]) {
                    g[i] = g[j] + 1;
                    f[i] = tmp;
                } else if (g[j] + 1 == g[i]) {
                    f[i] = (f[i] + tmp) % mod;
                }
            }
            l = max(l, g[i]);
        }
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            if (g[i] == l)
                ans = (ans + f[i]) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}