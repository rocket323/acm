#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <iostream>
using namespace std;
#define maxl 100010
#define ll long long
#define min(a,b) ((a) < (b) ? (a) : (b))
#define maxn 2010

ll n, m, a[maxl], b[maxl], k[maxl], p[maxl];
ll ans[11][maxn + 10];
ll f[maxn + 10];

int main() {
    while (scanf("%I64d%I64d", &n, &m) != EOF) {
    // while (cin >> n >> m) {
        for (ll i = 1; i <= n; ++i) {
            scanf("%I64d%I64d", &a[i], &b[i]);
            // cin >> a[i] >> b[i];
        }

        for (ll i = 1; i <= m; ++i) {
             scanf("%I64d%I64d", &k[i], &p[i]);
            // cin >> k[i] >> p[i];
        }

        for (ll d = 0; d <= 10; ++d) {
            for (ll i = 0; i <= maxn; ++i)
                f[i] = -1;
            f[0] = 0;

            for (ll i = 1; i <= maxn; ++i) {
                for (ll j = 1; j <= m; ++j) {
                    if (p[j] <= d) continue;
                    ll x = p[j] - d;

                    if (i >= x && f[i-x] != -1) {
                        if (f[i] == -1) f[i] = f[i-x] + k[j];
                        else f[i] = min(f[i], f[i-x] + k[j]);
                    }
                }
            }
            for (ll j = maxn-1; j >= 0; --j) {
                if (f[j] == -1) f[j] = f[j+1];
                else if (f[j+1] != -1) f[j] = min(f[j], f[j+1]);

                ans[d][j] = f[j];
            }
        }

        ll all = 0;
        for (ll i = 1; i <= n; ++i) {
            assert(a[i] >= 1 && a[i] <= 1000);
            assert(b[i] >= 0 && b[i] <= 10);

            ll x = ans[b[i]][a[i]];
            if (x == -1) {
                all = -1;
                break;
            }
            all += x;
            // if (all >= INF) break;
        }
        printf("%I64d\n", all);
        // cout << all << endl;
    }

    return 0;
}

