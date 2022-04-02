#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxl = 1e5 + 10;
int t, n, a[maxl];
ll f[maxl];
vector<int> adj[maxl];

void dfs2(int root, int u, ll total_sum, int mx) {
    ll child_sum = 0;
    for (int v : adj[u]) {
        child_sum += f[v];
    }
    for (int v : adj[u]) {
        ll tmp = child_sum - f[v];
        dfs2(root, v, total_sum + tmp, max(mx, a[v]));
    }
    if (adj[u].empty()) {
        f[root] = max(f[root], total_sum + mx);
    }
}

void dfs1(int u) {
    for (int v : adj[u]) {
        dfs1(v);
    }
    dfs2(u, u, 0, a[u]);
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
        dfs1(0);
        cout << "Case #" << tc << ": " << f[0] << endl;
    }
    return 0;
}