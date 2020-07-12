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
const ll maxl = 100010;
const ll mod = 1000000007;

ll n, w, k;
ll f[105][10], p[maxl], g[200];

ll P(ll n) {
    if (n < 0)
        return 0;
    return p[n];
}

void add(ll &a, ll b) {
    a = (a + b) % mod;
}

int main() {
    p[0] = 1;
    for (ll i = 1; i < maxl; i++)
        p[i] = (ll)p[i - 1] * 2 % mod;

    memset(g, 0, sizeof g);
    g[0] = 1;
    g[1] = 2;
    for (int i = 2; i < 10; i++) {
        g[i] = (g[i - 1] + g[i - 2]) % mod;
    }

    while (cin >> n >> w >> k) {
        memset(f, 0, sizeof f);
        f[n + 1][0] = 1;
        for (ll i = n + 1; i > 1; i--) {
            for (ll j = 0; j < w; j++) {
                if (f[i][j] == 0)
                    continue;

                ll c = 0;
                int l = j, r = w - 1 - j;
                if (l > 0) l--;
                if (r > 0) r--;;
                add(f[i - 1][j], f[i][j] * g[l] % mod * g[r] % mod);

                if (j + 1 < w) {
                    int l = j, r = w - 1 - (j + 1);
                    if (l > 0) l--;
                    if (r > 0) r--;
                    add(f[i - 1][j + 1], f[i][j] * g[l] % mod * g[r] % mod);
                }
                if (j - 1 >= 0) {
                    int l = j - 1, r = w - 1 - j;
                    if (l > 0) l--;
                    if (r > 0) r--;
                    add(f[i - 1][j - 1], f[i][j] * g[l] % mod * g[r] % mod);
                }
            }
        }
        cout << f[1][k - 1] << endl;
    }

    return 0;
}

