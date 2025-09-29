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

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

struct node {
    ll x, y, a, b, c;
} nd[maxl];

ll t, n, k;

int dd(ll a, ll b) {
    return (a + b - 1) / b;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> nd[i].x >> nd[i].y;
            ll price = dd(nd[i].x * nd[i].y, 10);
            ll dis = dd(dd(nd[i].x, 2) * nd[i].y, 10);
            nd[i].a = price;
            nd[i].b = dis;
            nd[i].c = price - dis;
        }
        sort(nd, nd + n, [](const node &l, const node &r) { return l.c > r.c; });
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (i < k) {
                ans = ans + nd[i].b;
            } else {
                ans = ans + nd[i].a;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
