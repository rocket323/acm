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

const ll inf = 0x3f3f3f3f;
const ll maxl = 1e4 + 10;
const ll mod = 998244353;

char s[maxl];
ll n, d[maxl];
int m, c[20];
int f[maxl][2][2][1024], cnt[maxl][2][2][1024], g[maxl];
int mask;

int gao() {
    memset(f, -1, sizeof f);
    f[0][0][0][0] = 0;
    cnt[0][0][0][0] = 1;
    for (ll i = 0; i < n; i++)
        d[i + 1] = s[i] - '0';
    ll t = 1023;
    for (ll i = 0; i < n; i++) {
        for (ll q = 0; q < 2; q++) {
            for (ll j = 0; j < 2; j++) {
                for (ll p = 0; p <= t; p++) {
                    if (cnt[i][q][j][p] == 0)
                        continue;

                    for (ll k = 0; k < 10; k++) {
                        if (j == 0 && k > d[i + 1])
                            break;

                        ll ii = i + 1;
                        ll qq = q | (k > 0);
                        ll jj = j | (k < d[i + 1]);
                        ll pp = p;
                        if (qq) {
                            pp = p | (1 << k);
                        }
                        ll x = g[n - ii];
                        ll tmp = (ll)k * x % mod * (ll)cnt[i][q][j][p] % mod;
                        if (f[ii][qq][jj][pp] < 0)
                            f[ii][qq][jj][pp] = 0;
                        f[ii][qq][jj][pp] = ((ll)f[ii][qq][jj][pp] + f[i][q][j][p] + tmp) % mod;
                        cnt[ii][qq][jj][pp] = ((ll)cnt[ii][qq][jj][pp] + cnt[i][q][j][p]) % mod;
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j <= t; j++) {
            if ((j & mask) != mask)
                continue;
            if (f[n][1][i][j] > 0)
                ans = (ans + f[n][1][i][j]) % mod;
        }
    }
    return ans;
}

int main() {
    scanf("%s", s);
    scanf("%d", &m);
    g[0] = 1;
    for (ll i = 1; i < maxl; i++)
        g[i] = (ll)g[i - 1] * 10 % mod;
    n = strlen(s);
    for (ll i = 0; i < m; i++) {
        scanf("%d", &c[i]);
        mask |= (1 << c[i]);
    }
    printf("%d\n", gao());
    return 0;
}
