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
const int maxl = 2010;

int t, n, d, c[maxl][maxl];
int f[maxl][maxl];

int dist(int i, int j) {
    return d * abs(i - j) + c[i][j];
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &d);
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                scanf("%d", &c[i][j]);
                c[j][i] = c[i][j];
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                f[i][j] = inf;
            }
        }

        f[1][1] = 0;
        int ans = inf;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (f[i][j] == inf)
                    continue;

                int k = max(i, j) + 1;
                f[k][j] = min(f[k][j], f[i][j] + dist(i, k));
                f[i][k] = min(f[i][k], f[i][j] + dist(j, k));

                if (i == n - 1 || j == n - 1) {
                    int tmp = f[i][j] + dist(i, n) + dist(j, n);
                    ans = min(ans, tmp);
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}

