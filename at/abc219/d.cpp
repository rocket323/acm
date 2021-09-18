#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxl = 305;
int n, x, y, a[maxl], b[maxl];
int f[maxl][maxl][maxl];

int main() {
    scanf("%d", &n);
    scanf("%d%d", &x, &y);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }

    memset(f, 0x3f, sizeof f);
    f[0][0][0] = 0;
    int ans = inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 301; j++) {
            for (int k = 0; k <= 301; k++) {
                if (f[i][j][k] == inf)
                    continue;

                int jj = j + a[i + 1] > 300 ? 301 : j + a[i + 1];
                int kk = k + b[i + 1] > 300 ? 301 : k + b[i + 1];

                f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k]);
                f[i + 1][jj][kk] = min(f[i + 1][jj][kk], f[i][j][k] + 1);
            }
        }
    }

    for (int j = x; j <= 301; j++) {
        for (int k = y; k <= 301; k++) {
            ans = min(ans, f[n][j][k]);
        }
    }
    printf("%d\n", ans == inf ? -1 : ans);

    return 0;
}
