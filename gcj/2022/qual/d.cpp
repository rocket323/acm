#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;
int t, n, a[maxl];
ll f[maxl], g[maxl];
vector<int> adj[maxl];

void dfs(int u) {
    ll child_sum = 0;
    int mg = inf;
    for (int v : adj[u]) {
        dfs(v);
        child_sum += f[v];
        if (g[v] < mg)
            mg = g[v];
    }

    g[u] = (mg == inf ? a[u] : max(mg, a[u]));
    if (adj[u].empty()) {
        f[u] = a[u];
    } else {
        for (int v : adj[u]) {
            ll tmp = child_sum;
            if (a[u] > g[v]) {
                tmp += a[u] - g[v];
            }
            f[u] = max(f[u], tmp);
        }
    }
}

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        memset(f, 0, sizeof f);
        for (int i = 0; i <= n; i++)
            adj[i].clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int u = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &u);
            adj[u].push_back(i);
        }
        dfs(0);
        cout << "Case #" << tc << ": " << f[0] << endl;
    }
    return 0;
}