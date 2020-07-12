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
#include <time.h>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

char s[maxl], t[maxl];
int n, m, q;
int f[10][maxl], g[maxl][10];

int main() {
    int tc;
    scanf("%d", &tc);
    srand(time(0));
    while (tc--) {
        scanf("%s", t);
        scanf("%s", s);

        m = strlen(t);
        n = strlen(s);

        for (int i = 0; i < min(n + 1, 6); i++) {
            if (i > 0)
                f[i][0] = s[i - 1] - '0';
            for (int j = 1; j <= m; j++) {
                if (i == 0)
                    f[i][j] = t[j - 1] - '0';
                else
                    f[i][j] = 1 - (f[i-1][j] * f[i][j-1]);

            }
        }

        for (int j = 0; j < min(m + 1, 6); j++) {
            if (j > 0)
                g[0][j] = t[j - 1] - '0';
            for (int i = 1; i <= n; i++) {
                if (j == 0)
                    g[i][j] = s[i - 1] - '0';
                else
                    g[i][j] = 1 - (g[i-1][j] * g[i][j-1]);
            }
        }

        /*
        for (int i = 0; i <= min(n, 5); i++) {
            for (int j = 0; j <= m; j++)
                printf("%d", f[i][j]);
            puts("");
        }
        puts("xx");
        for (int i = 0; i <= min(n, 5); i++) {
            for (int j = 0; j <= m; j++)
                printf("%d", g[i][j]);
            puts("");
        }
        puts("yy");
        */

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int r, c;
            scanf("%d%d", &r, &c);

            if (r < c) {
                if (r >= 4) {
                    r -= (r - 4);
                    c -= (r - 4);
                }
                printf("%d", f[r][c]);
            } else {
                if (c >= 4) {
                    c -= (c - 4);
                    r -= (c - 4);
                }
                printf("%d", g[r][c]);
            }

        }
        puts("");
    }

    return 0;
}

