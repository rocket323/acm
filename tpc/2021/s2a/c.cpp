#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;
const int mod = 1e9 + 7;
using ll = long long;
int t, n;
char s[maxl + 10];
int f[maxl + 10], g[maxl + 10];

ll pow(int a, int n) {
    ll ans = 1, t = a;
    while (n) {
        if (n & 1) {
            ans = (ll)ans * t % mod;
        }
        t = t * t % mod;
        n >>= 1;
    }
    return ans;
}

ll calc(int n, int m) {
    ll ans = 0;
    if (n < m) {
        return 0;
    } else {
        ans = (ll)f[n] * g[m] % mod * g[n - m] % mod;
    }
    // cout << n << ' ' << m << ' ' << ans << ' ' << f[m] << endl;
    return ans;
}

int main() {
    scanf("%d", &t);

    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i < maxl; i++) {
        f[i] = (ll)f[i - 1] * i % mod;
    }
    g[maxl - 1] = pow(f[maxl - 1], mod - 2);
    for (int i = maxl - 2; i >= 0; i--) {
        g[i] = (ll)g[i + 1] * (i + 1) % mod;
    }

    while (t--) {
        scanf("%s", s);
        // puts(s);
        int cnt = 0;
        n = strlen(s);
        for (int i = 0; i < n; i++) {
            if (s[i] == '1')
                cnt++;
        }
        ll ans = f[n];

        for (int i = 1; i <= cnt; i++) {
            ans = (ans + calc(cnt, i) * calc(n - 1, i) % mod * f[i] % mod * f[n - i] % mod) % mod;
        }
        cout << ans << endl;
    }

    return 0;
}