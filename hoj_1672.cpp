#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 1000010
#define mod 1000000007

int n, a[maxl], m, t;
int f[21][1<<20], g[21][1<<20];
int cnt[1<<20], p[maxl];

int main() {

    p[0] = 1;
    for (int i = 1; i <= maxl; ++i)
        p[i] = p[i-1] * 2 % mod;

    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            cnt[a[i]]++;
        }
        int I = 20;
        int tot = 1 << I;
        for (int i = 0; i < tot; ++i) {
            g[0][i] = cnt[i];
        }

        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= I; ++i) {
            for (int j = 0; j < tot; ++j) {
                int k = 1 << (i - 1);
                g[i][j] = g[i-1][j];
                if ((j & k) == 0)
                    g[i][j] = (g[i][j] + g[i-1][j+k]) % mod;

                if (i == I) cnt[j] = g[i][j];
            }
        }

        for (int i = 0; i < tot; ++i) {
            f[0][i] = (p[cnt[i]] + mod - 1) % mod;
        }

        for (int i = 1; i <= I; ++i) {
            for (int j = 0; j < tot; ++j) {
                int k = 1 << (i - 1);
                f[i][j] = f[i-1][j];
                if ((j & k) == 0)
                    f[i][j] = (f[i][j] + mod - f[i-1][j+k]) % mod;
            }
        }

        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d", &t);
            printf("%d ", f[I][t]);
        }
        puts("");
    }

    return 0;
}

