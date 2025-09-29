#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const ll inf = 3e18;

ll t, x, y;

ll calc(ll x, ll k, ll y) {
    ll drink = x;
    ll bottle = x;
    while (bottle >= k) {
        ll p = bottle / k;
        drink += p;
        if (drink > y + 10)
            return y + 10;
        bottle = bottle % k + p;
    }
    return drink;
}

ll calc0() {
    ll k = 1, drink = inf, l = 2, r = inf;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll c = calc(x, mid, y);
        if (c >= y + 1) {
            drink = c;
            k = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (drink != -1) {
        ll c = calc(x, k + 1, y);
        if (c == y) {
            return k + 1;
        }
    }

    return -1;
}

ll calc2() {
    ll k = -1, drink = -1, l = 2, r = inf;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll c = calc(x, mid, y);
        if (c >= y) {
            drink = c;
            k = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (drink == y)
        return k;

    return -1;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> x >> y;
        ll a = calc0();
        ll b = calc2();
        if (a == -1 && b == -1) {
            cout << "Impossible" << endl;
        } else if (a > b) {
            cout << "Impossible" << endl;
        } else if (b == inf) {
            cout << a << ' ' << "INF" << endl;
        } else {
            cout << a << ' ' << b << endl;
        }
    }
    return 0;
}
