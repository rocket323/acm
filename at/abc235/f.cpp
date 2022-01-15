#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e4 + 10;
const int mod = 998244353;

char s[maxl];
int n, m, c[maxl], d[maxl];
int f[maxl][2][2][1024], g[maxl];
int vis[maxl];

int gao() {
    memset(f, -1, sizeof f);
    f[0][0][0][0] = 0;
    for (int i = 0; i < n; i++)
        d[i + 1] = s[i] - '0';
    int t = (1 << m) - 1;
    for (int i = 0; i <= n; i++) {
        for (int q = 0; q < 2; q++) {
            for (int j = 0; j < 2; j++) {
                for (int p = 0; p <= t; p++) {
                    if (f[i][q][j][p] < 0)
                        continue;

                    // printf("%d %d %d %d %d\n", i, q, j, p, f[i][q][j][p]);
                    for (int k = 0; k < 10; k++) {
                        if (j == 0 && k > d[i + 1])
                            continue;

                        int ii = i + 1;
                        int qq = q | (k > 0);
                        int jj = j | (k < d[i + 1]);
                        int pp = p;
                        if (qq && vis[k] >= 0) {
                            pp = p | (1 << vis[k]);
                        }
                        int x = g[n - ii];
                        int tmp = (ll)k * x % mod;
                        if (f[ii][qq][jj][pp] < 0)
                            f[ii][qq][jj][pp] = 0;
                        f[ii][qq][jj][pp] = (f[ii][qq][jj][pp] + f[i][q][j][p] + tmp) % mod;
                        // printf("%d -> %d %d %d %d\n", k, ii, qq, jj, pp);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 2; i++) {
        if (f[n][1][i][t] > 0)
            ans = (ans + f[n][1][i][t]) % mod;
    }
    return ans;
}

int main() {
    scanf("%s", s);
    scanf("%d", &m);
    g[0] = 1;
    for (int i = 1; i < maxl; i++)
        g[i] = (ll)g[i - 1] * 10 % mod;
    n = strlen(s);
    for (int i = 0; i < 10; i++)
        vis[i] = -1;
    for (int i = 0; i < m; i++) {
        scanf("%d", &c[i]);
        vis[c[i]] = i;
    }
    printf("%d\n", gao());
    return 0;
}
