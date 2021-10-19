#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxl = 1e5 + 10;
typedef long long ll;

int tc, n, rr, a, b;
int x[maxl], t[maxl], w[maxl];

struct node {
    ll l, r;
} e[maxl];

bool cmp(const node &a, const node &b) {
    return a.r < b.r || (a.r == b.r && a.l < b.l);
}

bool check(ll c) {
    for (int i = 1; i <= n; i++) {
        if (c < t[i])
            return false;
        e[i].l = x[i] - (c - t[i]) / w[i] - rr;
        e[i].r = x[i] + (c - t[i]) / w[i] - rr;
        
        // cout << e[i].l << ' ' << e[i].r << endl;
    }

    sort(e + 1, e + 1 + n, cmp);
    ll last = a;
    for (int i = 1; i <= n; i++) {
        if (e[i].l > last)
            return false;
        ll p = min(e[i].r, last);
        last = max(last, p + 2 * rr);

        if (last >= b)
            return true;
    }

    return false;
}

int main() {
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d%d%d%d", &n, &rr, &a, &b);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &x[i], &t[i], &w[i]);
        }

        cout << check(5) << endl;

        ll l = 0, r = 1e7, ans = -1;
        while (l <= r) {
            ll mid = (l + r) / 2;
            bool k = check(mid);
            cout << mid << ' ' << k << endl;
            if (k) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}

