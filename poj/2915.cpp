#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int inf = 0x3f3f;
const int maxl = 2e5 + 10;

char t[maxl];
int n, m, a[maxl], b[maxl];
short f[201][201][40];
int pre[201];

inline short cost(short x, short y) {
    if (x + y >= m) {
        if (y > 0)
            return 0;
        return 1;
    }
    return m - (x + y);
}

inline short min(short a, short b) {
    return a < b ? a : b;
}

int main() {
    while (scanf("%d", &m) != EOF) {
        scanf("%s", t);
        int len = strlen(t);
        n = 0;
        for (int i = 0; i < len; i++) {
            if (i == 0 || t[i] != t[i - 1]) {
                ++n;
                a[n] = 1;
                b[n] = t[i] - 'A';
            } else {
                a[n]++;
            }
        }

        for (int i = 1; i <= n; i++) {
            pre[i] = 0;
            if (a[i] >= m)
                a[i] = m - 1;
            for (int j = i - 1; j >= 1; --j) {
                if (b[j] == b[i]) {
                    pre[i] = j;
                    break;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            f[i][i - 1][0] = 0;
        }
        int m2 = m * 2;
        short m21 = m2 - 1;
        short tmp = inf;
        short p = inf;
        short ajs = 0;
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i + k - 1 <= n; i++) {
                int j = i + k - 1;
                for (int s = 0; s < m2; s++) {
                    tmp = inf;
                    ajs = a[j] + s;
                    if (a[j] + s < m2)
                        tmp = min(tmp, f[i][j - 1][0] + cost(a[j], s));
                    for (int x = pre[j]; x >= i; x = pre[x]) {
                        p = f[x + 1][j - 1][0];
                        if (ajs < m) {
                            tmp = min(tmp, f[i][x][a[j] + s] + p);
                        } else if (s < m) {
                            tmp = min(tmp, f[i][x][a[j] + m] + p);
                        } else if (ajs < m21) {
                            tmp = min(tmp, f[i][x][a[j] + s] + p);
                        } else {
                            tmp = min(tmp, f[i][x][a[j]] + p);
                        }
                    }
                    f[i][j][s] = tmp;
                }
            }
        }
        int ans = f[1][n][0];
        printf("%d\n", ans);
    }
    return 0;
}