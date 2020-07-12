#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 310;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m, p;
int a[maxl][maxl];
int f[maxl][2];
int mm[maxl][maxl][maxl];
int s[maxl][maxl];

void update(int &a, int b) {
    if (b > -INF && b > a)
        a = b;
}

int solve(int l, int r) {
    for (int i = 0; i <= n; ++i)
        f[i][0] = f[i][1] = -INF;
    f[0][0] = 0;

    int ans = -INF;
    for (int i = 1; i <= n; ++i) {
        int ss = s[i][r] - s[i][l - 1];
        f[i][0] = max(ss, f[i - 1][0] + ss);

        update(f[i][1], f[i - 1][1] + ss);
        if (i > 1)
            update(f[i][1], ss);

        int x = mm[i][l][r];
        int add = p - x;
        int ns = ss + add;
        update(f[i][1], f[i - 1][0] + ns);
        update(f[i][1], ns);

        if (l == 1 && r == m && i == n)
            update(ans, f[i][1]);
        else
            update(ans, max(f[i][0], f[i][1]));
    }
    return ans;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &p) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            s[i][0] = 0;
            for (int j = 1; j <= m; ++j) {
                s[i][j] = s[i][j - 1] + a[i][j];

                mm[i][j][j] = a[i][j];
                for (int k = j + 1; k <= m; ++k) {
                    mm[i][j][k] = min(mm[i][j][k - 1], a[i][k]);
                }
            }
        }

        int ans = -INF;
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                ans = max(ans, solve(i, j));
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

