#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxl = 2e5 + 10;
int t, n, u, v, p;
vector<pair<int, int>> adj[maxl];
const ll inf = 1e16;
ll f[maxl][4];

int calc(int w) {
    return w & 1;
}

int calc1(int w) {
    return (w & 1) ^ 1;
}

void dfs(int u, int pre) {
    // f[u][0]: 没有边
    // f[u][1]: 只有偶数边, 或没有边
    // f[u][2]: 有一条单链
    // f[u][3]: 子树下有一条链，包括两条链经过自己

    f[u][0] = f[u][1] = 0;
    for (auto &kv : adj[u]) {
        int v = kv.first, w = kv.second;
        if (v == pre)
            continue;
        dfs(v, u);
        int t0 = calc(w), t1 = calc1(w);

        f[u][0] += f[v][0] + w;
        f[u][1] += min(f[v][0], f[v][1]) + t0;
        f[u][2] = min({f[u][1] + t1 + min({f[v][2], f[v][1], f[v][0]}), f[u][2] + t0 + min(f[v][1], f[v][0])});
        f[u][3] = min({f[u][0] + w + f[v][3], f[u][1] + t0 + f[v][3], f[u][2] + t1 + min({f[v][2], f[v][1], f[v][0]}),
                       f[u][3] + t0 + min(f[v][1], f[v][0])});
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            for (int j = 0; j < 4; j++)
                f[i][j] = inf;
        }
        for (int i = 0; i < n - 1; i++) {
            scanf("%d%d%d", &u, &v, &p);
            adj[u].push_back({v, p});
            adj[v].push_back({u, p});
        }

        dfs(1, 0);
        cout << min({f[1][0], f[1][1], f[1][2], f[1][3]}) << endl;
    }
    return 0;
}
