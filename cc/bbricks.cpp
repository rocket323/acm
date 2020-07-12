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
const int maxl = 2010;
const int mod = 1e9 + 7;

int t, n, k, tc;
int c[maxl][maxl];
int p[maxl];
int fac[maxl];
int qq[maxl];
int inv[maxl];

int main() {
    scanf("%d", &tc);
    
    for (int i = 0; i < maxl; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
        }
    }
    p[0] = 1;
    for (int i = 1; i < maxl; i++)
        p[i] = p[i - 1] * 2 % mod;

    inv[1] = 1;
    for (int i = 2; i < maxl; i++)
        inv[i]=(long long)(mod - mod / i) * inv[mod % i] % mod;

    fac[1] = 1;
    for (int i = 2; i < maxl; i++)
        fac[i] = (ll)fac[i - 1] * inv[i] % mod;

    while (tc--) {
        scanf("%d%d", &n, &k);

        int q = n - k + 1;
        qq[0] = q;
        for (int i = 1; i < maxl; i++)
            qq[i] = (ll)qq[i - 1] * (q - i) % mod;

        int ans = 0;
        for (int t = 1; t <= k; t++) {
            int tmp = (ll)p[t] * c[k-1][t-1] % mod;
            int a = n - k - (t - 1);
            int b = t + 1;
            if (a >= 0 && q >= t) {
                // int x = c[a + b - 1][b - 1];
                int x = (ll)qq[t - 1] * fac[t] % mod;
                tmp = (ll)tmp * x % mod;
                ans = (ans + tmp) % mod;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

