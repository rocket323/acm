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

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int t, n, k, a[maxl];
ll s, sq;

void gao1() {
    ll x = 0, c = 0;
    for (int i = 1; i <= n; i++) {
        x += a[i];
        c += (ll)a[i] * a[i];
    }

    if (x == 0) {
        if (c > 0)
            puts("IMPOSSIBLE");
        else
            puts("0");
    } else {
        ll m = c - x * x;
        if (m % (2 * x) == 0) {
            cout << m / (2 * x) << endl;
        } else {
            puts("IMPOSSIBLE");
        }
    }
}

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d", &n, &k);
        s = 0;
        sq = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            s += a[i];
            sq += (ll)a[i] * a[i];
        }
        printf("Case #%d: ", tc);
        if (k == 1) {
            gao1();
        } else {
            ll n1 = 1 - s;
            a[n + 1] = n1;
            ll sp = 0;
            for (int i = 1; i <= n + 1; i++) {
                for (int j = i + 1; j <= n + 1; j++) {
                    sp += (ll)a[i] * a[j];
                }
            }
            ll n2 = -sp;
            cout << n1 << ' ' << n2 << endl;
        }
    }
    return 0;
}