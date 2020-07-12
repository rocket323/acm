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
const int maxl = 100010;
const int mod = 1e9 + 7;

int t, n, k, a[maxl];
ll f[55][maxl];
int l[maxl], r[maxl];

ll solve() {
    for (int i = 1; i <= n; ++i) {
        l[i] = i;
        r[i] = i;
        while (i > 1 && a[l[i] - 1] >= a[i]) l[i]--;
        while (i < n && a[r[i] + 1] >= a[i]) r[i]++;
    }
    memset(f, 0, sizeof f);

    ll ans = 0;
    for (int x = 1; x <= k + 1; ++x) {
        for (int i = 1; i <= n; ++i) {
            ll t2 = (ll)a[i] * (i - l[i] + 1);

            for (int j = l[i] - 1; j >= 0; --j) {
                if (a[j] > a[j + 1]) break;
                ll t1 = 0;
                if (f[x - 1][j] > 0)
                    t1 = (ll)a[j] * (l[i] - j - 1);
                ll w = t1 + t2;

                f[x][i] = max(f[x][i], f[x - 1][j] + w);
            }

            ll tmp = f[x][i] + (ll)a[i] * (r[i] - i);
            ans = max(ans, tmp);
        }
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);

        ll ans = 0;
        ans = max(ans, solve());
        reverse(a + 1, a + 1 + n);
        ans = max(ans, solve());

        printf("%lld\n", ans);
    }

    return 0;
}

