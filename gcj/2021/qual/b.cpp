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
const int maxl = 1e5 + 10;

int t, n, f[maxl][2], x, y;
char s[maxl];

int get(char ch) {
    if (ch == 'C')
        return 0;
    return 1;
}

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d%s", &x, &y, s);
        n = strlen(s);

        memset(f, 0x3f, sizeof f);
        f[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                if (f[i][j] == inf)
                    continue;

                for (int k = 0; k < 2; k++) {
                    if (s[i] != '?' && get(s[i]) != k)
                        continue;

                    int w = 0;
                    if (i > 0) {
                        if (j == 0 && k == 1)
                            w = x;
                        if (j == 1 && k == 0)
                            w = y;
                    }
                    f[i + 1][k] = min(f[i + 1][k], f[i][j] + w);
                }
            }
        }
        printf("Case #%d: %d\n", tc, min(f[n][0], f[n][1]));
    }
    return 0;
}
