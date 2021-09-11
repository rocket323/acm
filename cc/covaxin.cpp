#include <stdio.h>
#include <cstring>
#include <iostream>

using namespace std;
using ll = long long;
ll I, x, a, b, c, d, p, q, r, s, t, m;
ll ans, A, B, C;
const ll inf = 1e18;

ll f(ll i) {
    if (i > 0 && A > 0 && x / A / i / i < 1)
        return inf;
    ll ans = A * i * i;
    if (i > 0 && B > 0 && x / B / i < 1)
        return inf;
    ans += B * i;
    if (ans > x)
        return inf;
    ans += C;
    return ans;
}

ll gao(ll n) {
    A = b + d;

    B = 2 * a - b - (n * d + 2 * c + (n - 1) * d);
    C = n * (2 * c + (n - 1) * d);

    ll ans = inf;
    ll xx = 0 - B / (2 * A);
    if (xx >= 0 && xx <= n) {
        ans = min(ans, f(xx));
    }
    if (xx - 1 >= 0 && xx - 1 <= n) {
        ans = min(ans, f(xx - 1));
    }
    if (xx + 1 >= 0 && xx + 1 <= n) {
        ans = min(ans, f(xx + 1));
    }

    ans = min(ans, f(0));
    ans = min(ans, f(n));
    return ans / 2;
}

ll solve() {
    ll l = 1, r = 4e9;
    ll ans = 0;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll tmp = gao(mid);
        if (tmp <= x) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return ans;
}

int main() {
    cin >> I;
    cin >> x >> a >> b >> c >> d;
    cin >> p >> q >> r >> s >> t >> m;

    for (int i = 1; i <= I; i++) {
        ans = solve();

        a = (a + ans * t) % m + p;
        b = (b + ans * t) % m + q;
        c = (c + ans * t) % m + r;
        d = (d + ans * t) % m + s;

        cout << ans << endl;
    }

    return 0;
}

