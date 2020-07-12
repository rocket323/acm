#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 105

int n, m, v[maxl], c[maxl];
int f[105][1010], g[105][1010], p[105][1010], t;

void solve() {
    memset(f, 0x80, sizeof f);
    for (int i = 0; i <= m; ++i)
        f[n + 1][i] = 0;

    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= m; ++j) {
            f[i][j] = f[i + 1][j];
            if (j + c[i] <= m)
                f[i][j] = max(f[i][j], f[i + 1][j + c[i]] + v[i]);
        }
    }

    memset(g, 0x3f, sizeof g);
    for (int i = 0; i <= m; ++i)
        g[n + 1][i] = 0;

    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= m; ++j) {
            if (f[i][j] == f[i + 1][j]) 
                g[i][j] = g[i + 1][j];
            
            if (j + c[i] <= m) {
                if (f[i][j] == f[i + 1][j + c[i]] + v[i])
                    g[i][j] = min(g[i][j], g[i + 1][j + c[i]] + i);
            }
        }
    }

    memset(p, 0x80, sizeof p);
    for (int i = 0; i <= m; ++i)
        p[n + 1][i] = 0;

    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= m; ++j) {
            if (f[i][j] == f[i + 1][j] && g[i][j] == g[i + 1][j])
                p[i][j] = p[i + 1][j];

            if (j + c[i] <= m) {
                if (f[i][j] == f[i + 1][j + c[i]] + v[i] &&
                        g[i][j] == g[i + 1][j + c[i]] + i)
                    p[i][j] = max(p[i][j], p[i + 1][j + c[i]] + 1);
            }
        }
    }

    // printf("f %d %d\n", f[2][0], f[2][10] + 10);
    // printf("g %d %d\n", g[2][0], g[2][10] + 1);
    std::vector<int> vec;
    int j = 0;
    for (int i = 1; i <= n; ++i) {
        int f0 = f[i + 1][j], g0 = g[i + 1][j];
        int f1 = f[i + 1][j + c[i]] + v[i];
        int g1 = g[i + 1][j + c[i]] + i;
        int p0 = p[i + 1][j];
        int p1 = p[i + 1][j + c[i]] + 1;

        // printf("%d %d: %d %d, %d %d\n", i, j, f0, g0, f1, g1);

        bool choose = false;
        if (f0 > f1) {
        } else if (f0 < f1) {
            choose = true;
        } else {
            if (g0 < g1) {
            } else if (g0 > g1) {
                choose = true;
            } else {
                if (p0 < p1) {
                    choose = true;
                } else if (p0 > p1) {
                } else {
                }
            }
        }
        // printf("%d %d\n", i, choose);

        if (choose) {
            j = j + c[i];
            vec.push_back(i);
        }
    }
    
    printf("%d %d\n", f[1][0], j);
    for (size_t i = 0; i < vec.size(); ++i) {
        printf("%d ", vec[i]);
        if (i == vec.size() - 1)
            puts("");
    }
}

int main() {
    scanf("%d", &t);
    for (int x = 1; x <= t; ++x) {
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &v[i], &c[i]);

        printf("Case #%d:\n", x);
        solve();
    }

    return 0;
}

