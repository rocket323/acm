#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#define maxl 200010
using namespace std;
#define ll long long

struct node {
    ll l, r;
} nd[maxl], nd2[maxl];

bool cmp(const node &a, const node &b) {
    return a.l < b.l || (a.l == b.l && a.r > b.r);
}

ll n, m, c[maxl];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    while (cin >> n >> m) {
        for (ll i = 1; i <= n; ++i) {
            cin >> nd2[i].l >> nd2[i].r;
        }
        sort(nd2 + 1, nd2 + 1 + n, cmp);
        memset(c, 0, sizeof c);

        int top = 0;
        nd[++top] = nd2[1];
        for (int i = 2; i <= n; ++i) {
            if (nd2[i].r > nd[top].r) {
                nd[++top] = nd2[i];
            }
        }
        n = top;

        for (ll i = 1; i < n; ++i) {
            if (nd[i+1].l > nd[i].r + 1)
                c[i] = nd[i+1].l - nd[i].r - 1;
        }

        ll ans = 0;
        ll sm = m;
        ll curR = 1;
        for (ll i = 1; i <= n; ++i) {
            ll cost = c[i-1];

            if (curR < i) {
                m = sm;
                curR = i;
            } else {
                m += cost;
            }

            while (curR < n) {
                ll cost = c[curR];
                if (cost <= m) {
                    m -= cost;
                    curR++;
                } else {
                    break;
                }
            }

            ll r = nd[curR].r;
            ll tmp = r  - nd[i].l + 1 + m;
            ans = max(ans, tmp);
        }

        cout << ans << endl;
    }

    return 0;
}

