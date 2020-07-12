#include <stdio.h>
#include <cstring>
#include <algorithm>
#define maxl 1010
#define INF 0x3f3f3f3f
using namespace std;

int n, a[maxl], p[maxl];
// 处理完数i，移动的数的最右位置为j时，最少的移动数。
int f[maxl][maxl][2];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            p[a[i]] = i;
        }

        memset(f, 0x3f, sizeof f);
        f[n][p[n]] = 0;
        f[n][0] = 1;

        for (int i = n; i > 1; --i) {
            for (int j = 0; j <= n; ++j) {
                if (f[i][j] >= INF) continue;

                int x = p[i-1];
                f[i-1][j] = min(f[i-1][j], f[i][j] + 1);

                if (x > j)
                    f[i-1][x] = min(f[i-1][x], f[i][j]);
            }
        }
        int ans = INF;
        for (int i = 0; i <= n; ++i)
            ans = min(ans, f[1][i]);
        printf("%d\n", ans);
    }

    return 0;
}

