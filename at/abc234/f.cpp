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
const int maxl = 5050;
const int mod = 998244353;

char s[maxl];
int n, c[maxl], f[30][5050];
int g[5050][5050];

void add(int &a, int b) {
    a = (a + b) % mod;
}

int main() {
    for (int i = 1; i < maxl; i++) {
        g[i][0] = g[i][i] = 1;
        for (int j = 1; j < i; j++) {
            g[i][j] = (g[i - 1][j - 1] + g[i - 1][j]) % mod;
        }
    }

    scanf("%s", s);
    n = strlen(s);
    for (int i = 0; i < n; i++) {
        c[s[i] - 'a' + 1]++;
    }

    f[0][0] = 1;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j <= n; j++) {
            if (f[i][j] == 0)
                continue;

            add(f[i + 1][j], f[i][j]);
            for (int k = 1; k <= c[i + 1]; k++) {
                ll t = g[j + k][k];
                add(f[i + 1][j + k], (ll)f[i][j] * t % mod);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        add(ans, f[26][i]);
    }
    cout << ans << endl;

    return 0;
}
