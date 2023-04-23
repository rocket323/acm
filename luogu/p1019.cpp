#include <algorithm>
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

int n;
char s[101][101], ch[10];
int g[101][101], f[(1 << 20) + 10][21];
int L[101];

int gao(int i, int j) {
    for (int x = 0; s[i][x]; x++) {
        int l = strlen(s[i] + x);
        if (strncmp(s[i] + x, s[j], l) == 0) {
            return l;
        }
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        L[i] = strlen(s[i]);
    }
    scanf("%s", ch);
    cout << ch << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = gao(i, j);
        }
    }
    memset(f, 0x80, sizeof f);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i][0] == ch[0]) {
            f[1 << i][i] = L[i];
            printf("%d %d\n", i, f[(1 << i)][i]);
        }
    }
    int mask = (1 << n) - 1;
    for (int i = 0; i <= mask; i++) {
        for (int j = 0; j < n; j++) {
            if (f[i][j] < 0)
                continue;

            ans = max(ans, f[i][j]);
            for (int k = 0; k < n; k++) {
                if (i & (1 << k))
                    continue;

                if (g[j][k] < 0)
                    continue;

                f[i | (1 << k)][k] = max(f[i | (1 << k)][k], f[i][j] + L[k] - g[j][k]);
                cout << i << ' ' << j << ' ' << f[i][j] << ':' << k << ' ' << f[i | (1 << k)][k] << endl;
            }
        }
    }
    cout << ans << endl;
    return 0;
}