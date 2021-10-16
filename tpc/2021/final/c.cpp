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
const int maxl = 1e5 + 10;

ll t, a, b, c, d, k;
ll ans;

ll gao(ll a, ll b, ll c, ll d, ll k) {
    // ll m = b % 5;
    // if (m > 0 && d >= (5 - m)) {
    //     d -= (5 - m);
    //     b += (5 - m);
    // }

    ll p = (c + 2) / 3 * 3;
    if (p <= 3 * k && p >= c && d >= p - c) {
        d -= (p - c);
        c = p;
    }

    if ((ll)c < (ll)3 * k) {
        ll x = min((ll)3 * k - c, (ll)d / 3 * 3);
        d -= x;
        c += x;
    }

    a += d;

    // printf("%d %d %d %d\n", a, b, c, k);
    // cout << a << ' ' << b << ' ' << c << ' ' << k << endl;

    ll ans = 0;
    if (c > 0 && c < 3) {
        k--;
        c = 0;
    }

    ans += (ll)min(c / 3, k) * 10;
    if (k > 0) {
        ans += (ll)b / 5 * 15 + b % 5;
        ans += (ll)a * 3;
    }
    // printf("%d %d %d\n", a * 3, b / 5 * 15 + b % 5, c / 3 * 10);
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // scanf("%d", &t);
    cin >> t;
    while (t--) {
        // scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        cin >> a >> b >> c >> d >> k;

        ans = 0;
        for (ll i = 0; i < 5 & i <= d; i++) {
            ll tmp = gao(a, b + i, c, d - i, k);
            ans = max(ans, tmp);
        }

        cout << ans << endl;
    }
    return 0;
}

