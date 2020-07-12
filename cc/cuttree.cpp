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
const ll mod = 1e9 + 7;

vector<ll> adj[maxl];
ll d[maxl], n;
ll c[1010][1010];
ll ans[maxl];

void dfs(ll u, ll pre, ll len) {
    d[len]++;
    for (auto v : adj[u]) {
        if (v == pre) continue;
        dfs(v, u, len + 1);
    }
}

ll pow(ll a, ll n) {
    ll ans = 1;
    ll t = a;
    while (n) {
        if (n & 1) ans = ans * t % mod;
        n >>= 1;
        t = t * t % mod;
    }
    return ans;
}

int main() {
    cin >> n;
    for (ll i = 1; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (n >= 1010) return 0;

    memset(c, 0, sizeof c);
    c[0][0] = 1;
    for (ll i = 1; i < 1010; i++) {
        c[i][0] = c[i][i] = 1;
        for (ll j = 1; j < i; j++) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
        }
    }

    memset(d, 0, sizeof d);
    for (ll i = 1; i <= n; i++)
        dfs(i, -1, 0);

    for (ll i = 0; i < n; i++) {
        for (ll j = i; j < n; j++) {
            ll x = (j - i);
            ll tmp = (ll)c[n - 1 - i][x] * d[i] % mod;
            ans[j] = (ans[j] + tmp) % mod;
        }
    }

    for (ll i = 0; i < n; i++) {
        ll tmp = pow(c[n-1][i], mod - 2);
        ans[i] = (ll)ans[i] * tmp % mod;
    }
    reverse(ans, ans + n);

    for (ll i = 0; i < n; i++) {
        cout << ans[i];
        if (i == n - 1) cout << endl;
        else cout << ' ';
    }

    return 0;
}

