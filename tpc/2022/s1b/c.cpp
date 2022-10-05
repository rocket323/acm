#include <bits/stdc++.h>
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

const ll inf = 1e15;
const ll maxl = 6e5 + 10;
const ll maxe = 1e6 + 10;
const ll mod = 998244353;

ll n, a[maxl], f[maxl], g[maxl];
ll c[maxl], t, m, L[35][maxl];
int cnt[maxe];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    cin >> t;
    while (t--) {
        // scanf("%d", &n);
        cin >> n;
        for (int i = 1; i <= n; i++) {
            // scanf("%d", &a[i]);
            cin >> a[i];
            cnt[a[i]] = 0;
        }
        // scanf("%d", &m);
        cin >> m;
        for (int i = 0; i <= m; i++) {
            // scanf("%d", &c[i]);
            cin >> c[i];
        }

        for (int j = 1; j <= m; j++) {
            int last = 1;
            int cur_cnt = 1;
            cnt[a[1]] = 1;
            for (int i = 2; i <= n; i++) {
                bool is_new = (cnt[a[i]] == 0);
                cnt[a[i]]++;
                if (is_new) {
                    cur_cnt++;
                    while (cur_cnt > j) {
                        cnt[a[last]]--;
                        if (cnt[a[last]] == 0) {
                            cur_cnt--;
                        }
                        last++;
                    }
                    L[j][i] = last;
                } else {
                    L[j][i] = last;
                }
                // cout << j << ' ' << i << ' ' << L[j][i] << endl;
            }
            for (int j = 1; j <= n; j++)
                cnt[a[j]] = 0;
        }

        for (int i = 0; i <= n; i++) {
            f[i] = inf;
            g[i] = 0;
        }
        f[0] = 0;
        g[0] = 1;

        for (int i = 1; i <= n; i++) {
            f[i] = f[i - 1] + c[0];
            g[i] = g[i - 1];

            for (int j = 1; j <= m; j++) {
                int x = L[j][i];
                if (f[x - 1] >= inf)
                    continue;

                if (f[x - 1] + c[j] < f[i]) {
                    f[i] = f[x - 1] + c[j];
                    g[i] = g[x - 1];
                } else if (f[x - 1] + c[j] == f[i]) {
                    g[i] = (g[i] + g[x - 1]) % mod;
                }
            }
            // cout << i << ' ' << f[i] << endl;
        }

        cout << f[n] << ' ' << g[n] << endl;
    }
    return 0;
}