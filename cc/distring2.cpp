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
#include <unordered_map>
using namespace std;

typedef long long ll;
const int maxl = 500010;
const int mod = 1e9 + 7;
const int maxn = 2000;

vector<vector<int>> a;
int n, m;
int p[maxn][maxn];

ll solve1() {
    ll ans = 0;
    for (int l = 1; l <= m; l++) {
        for (int i = 1; i <= n; i++) {
            int mx = l;
            ll sum = 0;
            for (int j = i; j >= 1; j--) {
                if (j != i) {
                    if (p[i][j] < l) {
                        p[i][j] = l;

                        while (p[i][j] <= m && a[i][p[i][j]] == a[j][p[i][j]])
                            p[i][j]++;
                    }
                    mx = max(mx, p[i][j]);
                }
                sum += m - mx + 1;
            }
            ans += sum * (n - i + 1);
        }
    }
    return ans;
}

int last[maxl];
unordered_map<int, int> nodes[maxl];
int top;

ll solve2() {
    ll ans = 0;
    for (int l = 1; l <= m; l++) {
        top = 0;
        nodes[top++].clear();
        for (int i = 1; i <= n; i++) {
            int now = 0;
            for (int r = l; r <= m; r++) {
                if (nodes[now].count(a[i][r])) {
                    now = nodes[now][a[i][r]];
                } else {
                    nodes[top].clear();
                    nodes[now][a[i][r]] = top;
                    now = top++;
                    last[now] = 0;
                }

                ans += (ll)(i - last[now]) * (n - i + 1);
                last[now] = i;
            }
        }
    }

    return ans;
}

int main() {
    scanf("%d%d", &n, &m);

    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].resize(m + 1);
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    if (n <= maxn)
        cout << solve1() << endl;
    else
        cout << solve2() << endl;

    return 0;
}

