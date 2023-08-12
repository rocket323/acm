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
const int maxl = 2e5 + 10;
const int mod = 1e9 + 7;

int t, n, k;
int c[maxl], f[105][105], cnt[105][105], C[105][105];
bool vis[105][105];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                f[i][j] = 0;
                vis[i][j] = false;
                C[i][j] = 0;
                cnt[i][j] = 0;
            }
        }
        vis[0][0] = 1;
        f[0][0] = 1;
        C[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                for (int x = i; x <= j; x++) {
                    if (c[x] == c[j])
                        cnt[i][j]++;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                C[i][j] = ((ll)C[i - 1][j] + C[i - 1][j - 1]) % mod;
            }
        }
        int m = n / k;
        int l = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int p = 0; p < i; p++) {
                    if (!vis[p][j - 1])
                        continue;
                    int x = cnt[p + 1][i];
                    if (x < k)
                        continue;

                    vis[i][j] = true;
                    int tmp = (ll)C[x - 1][k - 1] * f[p][j - 1] % mod;
                    f[i][j] = (f[i][j] + tmp) % mod;
                }
                if (vis[i][j] && j > l)
                    l = j;
            }
        }
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            if (vis[i][l])
                ans = (ans + f[i][l]) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}