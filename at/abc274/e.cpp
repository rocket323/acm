#include <algorithm>
#include <cmath>
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

int n, m;
int x[20], y[20], p[20], q[20];
double f[5000][35][18];
bool g[5000][35][15];

ll sq(ll x) {
    return x * x;
}

double dist(ll x1, ll y1, ll x2, ll y2, double sp) {
    return sqrt(sq(x1 - x2) + sq(y1 - y2)) / sp;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &p[i], &q[i]);
    }
    int m1 = (1 << n) - 1;
    int m2 = (1 << m) - 1;
    for (int s1 = 0; s1 <= m1; s1++) {
        for (int s2 = 0; s2 <= m2; s2++) {
            for (int i = 0; i < n + m; i++) {
                f[s1][s2][i] = 1e17;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        g[1 << i][0][i] = 1;
        f[1 << i][0][i] = dist(0, 0, x[i], y[i], 1);
    }
    for (int i = 0; i < m; i++) {
        g[0][1 << i][i + n] = 1;
        f[0][1 << i][i + n] = dist(0, 0, p[i], q[i], 1);
    }

    for (int s1 = 0; s1 <= m1; s1++) {
        for (int s2 = 0; s2 <= m2; s2++) {
            for (int i = 0; i < n + m; i++) {
                if (!g[s1][s2][i])
                    continue;

                int sp = 1;
                int t = s2;
                while (t > 0) {
                    if (t & 1)
                        sp *= 2;
                    t >>= 1;
                }

                if (i < n) {
                    for (int j = 0; j < n; j++) {
                        if (s1 & (1 << j))
                            continue;
                        g[s1 | (1 << j)][s2][j] = 1;
                        f[s1 | (1 << j)][s2][j] =
                            min(f[s1 | (1 << j)][s2][j], f[s1][s2][i] + dist(x[i], y[i], x[j], y[j], sp));
                    }
                    for (int j = 0; j < m; j++) {
                        if (s2 & (1 << j))
                            continue;
                        g[s1][s2 | (1 << j)][j + n] = 1;
                        f[s1][s2 | (1 << j)][j + n] =
                            min(f[s1][s2 | (1 << j)][j + n], f[s1][s2][i] + dist(x[i], y[i], p[j], q[j], sp));
                    }
                } else {
                    for (int j = 0; j < n; j++) {
                        if (s1 & (1 << j))
                            continue;
                        g[s1 | (1 << j)][s2][j] = 1;
                        f[s1 | (1 << j)][s2][j] =
                            min(f[s1 | (1 << j)][s2][j], f[s1][s2][i] + dist(p[i - n], q[i - n], x[j], y[j], sp));
                    }
                    for (int j = 0; j < m; j++) {
                        if (s2 & (1 << j))
                            continue;
                        g[s1][s2 | (1 << j)][j + n] = 1;
                        f[s1][s2 | (1 << j)][j + n] =
                            min(f[s1][s2 | (1 << j)][j + n], f[s1][s2][i] + dist(p[i - n], q[i - n], p[j], q[j], sp));
                    }
                }
            }
        }
    }

    double ans = 1e17;
    for (int s2 = 0; s2 <= m2; s2++) {
        int sp = 1;
        int t = s2;
        while (t > 0) {
            if (t & 1)
                sp *= 2;
            t >>= 1;
        }
        for (int i = 0; i < n; i++) {
            double tmp = f[m1][s2][i] + dist(x[i], y[i], 0, 0, sp);
            ans = min(ans, tmp);
        }
        for (int i = 0; i < m; i++) {
            double tmp = f[m1][s2][i + n] + dist(p[i], q[i], 0, 0, sp);
            ans = min(ans, tmp);
        }
    }
    printf("%.8lf\n", ans);

    return 0;
}