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

const ll inf = 1e16;
const int maxl = 2e5 + 10;

int t, n, p;
ll ans;
ll f[1010][2];
int x[1010][105];

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d", &n, &p);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < p; j++) {
                scanf("%d", &x[i][j]);
            }
            sort(x[i], x[i] + p);
        }
        for (int i = 0; i <= n; i++) {
            f[i][0] = f[i][1] = inf;
        }
        f[0][0] = f[0][1] = 0;
        x[0][0] = x[0][p - 1] = 0;
        ll ans = inf;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 2; j++) {
                ll p2 = (j == 0 ? x[i][0] : x[i][p - 1]);
                for (int k = 0; k < 2; k++) {
                    ll p1 = (k == 0 ? x[i - 1][p - 1] : x[i - 1][0]);
                    if (f[i - 1][k] >= inf)
                        continue;
                    ll tmp = f[i - 1][k] + abs(p1 - p2) + (x[i][p - 1] - x[i][0]);
                    f[i][j] = min(f[i][j], tmp);
                    // cout << i << ' ' << j << ' ' << k << ' ' << f[i - 1][k] << ' ' << ' ' << p1 << ' ' << p2 << ' '
                    //      << abs(p1 - p2) << ' ' << (x[i][p - 1] - x[i][0]) << ' ' << tmp << ' ' << f[i][j] << endl;
                }
                if (i == n)
                    ans = min(ans, f[i][j]);
                // cout << i << ' ' << j << ' ' << f[i][j] << endl;
            }
        }
        cout << "Case #" << tc << ": " << ans << endl;
    }
    return 0;
}