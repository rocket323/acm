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
const int maxl = 1010;
const int mod = 1e9 + 7;

int n, m;
int a[maxl][maxl];
vector<int> dp[maxl * maxl];
int last[maxl];

int get_idx(int r, int c) {
    return (r - 1) * n + c - 1;
}

ll solve(int c1, int c2) {
    for (int i = 1; i <= n; i++) {
        last[i] = 0;
        for (int j = i - 1; j >= 1; j--) {
            int idx = get_idx(i, j);
            auto iter = lower_bound(dp[idx].begin(), dp[idx].end(), c1);
            if (iter == dp[idx].end() || *iter > c2) {
                last[i] = j;
                break;
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll cnt = 0;
        for (int j = i; j <= n; j++) {
            if (last[j] < i)
                cnt++;
            ans += cnt;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    if (n * m >= 2000)
        return 0;

    // a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        // a[i].resize(m + 1);
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n * m; i++)
        dp[i].clear();
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int idx = get_idx(i, j);
            for (int k = 1; k <= m; k++) {
                if (a[i][k] != a[j][k])
                    dp[idx].push_back(k);
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j++) {
            ll tmp = solve(i, j);
            ans += tmp;
        }
    }
    cout << ans << endl;

    return 0;
}

