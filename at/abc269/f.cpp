#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const ll inf = 0x3f3f3f3f;
const ll maxl = 2e5 + 10;
ll mod = 998244353;

ll n, m, q, a, b, c, d;
ll ni;

ll pow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

ll getsum(ll row, ll c, ll d, ll &cols) {
    ll ans = 0;
    ll l = (ll)(row - 1) * m + c;
    ll r = (ll)(row - 1) * m + d;
    if ((row + c) & 1)
        l++;
    if ((row + d) & 1)
        r--;

    cols = 0;
    if (l > r)
        return 0;

    cols = (r - l) / 2 + 1;
    ans = (l + r) % mod * cols % mod * ni % mod;
    return ans;
}

ll add(ll a, ll d, ll cnt) {
    ll ans = (a + a + d * (cnt - 1)) % mod * cnt % mod * ni % mod;
    return ans;
}

ll gao(ll a, ll b, ll c, ll d) {
    ll cols0 = 0, cols1 = 0;
    ll s0 = getsum(a, c, d, cols0);
    ll s1 = getsum(a + 1, c, d, cols1);

    ll cnt = (b - a + 1);
    ll c0 = cnt / 2, c1 = cnt / 2;
    if (cnt & 1)
        c0++;

    ll add0 = (ll)m * cols0 * 2 % mod;
    ll add1 = (ll)m * cols1 * 2 % mod;

    ll ans0 = add(s0, add0, c0);
    ll ans1 = add(s1, add1, c1);
    return (ans0 + ans1) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    ni = pow(2, mod - 2);
    cin >> n >> m;
    cin >> q;
    for (ll i = 1; i <= q; i++) {
        cin >> a >> b >> c >> d;
        cout << gao(a, b, c, d) << endl;
    }
    return 0;
}