#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int maxl = 2e6 + 10;
const int mod = 998244353;
int n, d, f[maxl];

int main() {
    scanf("%d%d", &n, &d);
    ll ans = 0;

    f[0] = 1;
    for (int i = 1; i < maxl; i++)
        f[i] = ((ll)f[i-1] * 2) % mod;

    for (int i = 1; i <= n; i++) {
        ll cnt = f[i - 1];

        if (n - i >= d) {
            ll tmp = (cnt * 2 * f[d]) % mod;
            ans = (ans + tmp) % mod;
        }

        int j = (i + n - d) / 2;
        if (j < 1 || j >= i)
            continue;
        
        int l = d - (i - j + 1);
        if (l < 0)
            continue;

        if (i <= d) { 
            ll tmp = (ll)cnt * (f[l+1] + mod - f[d - i]) % mod;
            ans = (ans + tmp) % mod;
        } else {
            ll tmp = (ll)cnt * (f[l+1] + mod - 1) % mod;
            ans = (ans + tmp) % mod;
        }
    }
    cout << ans << endl;

    return 0;
}

