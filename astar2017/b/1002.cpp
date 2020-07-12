#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 100010

const int LOG = 20;
int n, m, u, t;
int f[maxl][20], dist[maxl], dep[maxl];
vector<pair<int, int>> adj[maxl];
vector<int> office[maxl];

void dfs(int x, int p) {
    f[x][0] = p;
    for (int i = 1; i < LOG; ++i) {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (auto &y : adj[x]) {
        if (y.first != p) {
            dist[y.first] = dist[x] + y.second;
            dep[y.first] = dep[x] + 1;
            dfs(y.first, x);
        }
    }
}

int up(int x, int h) {
    int i = 0;
    while (h) {
        if (h & 1) {
            x = f[x][i];
        }
        h >>= 1;
        i++;
    }
    return x;
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    if (dep[u] < dep[v]) v = up(v, dep[v] - dep[u]);

    while (u != v) {
        for (int i = LOG - 1; i >= 0; --i) {
            if (f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        if (f[u][0] == f[v][0]) {
            u = v = f[u][0];
        }
    }
    return u;
}

int main() {
    int t, u, v, w;
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n-1; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }

        for (int i = 1; i <= m; ++i) {
            int g, x;
            scanf("%d", &g);
            for (int j = 0; j < g; ++j) {
                scanf("%d", &x);
                office[i].push_back(x);
            }
        }
        dfs(1, 0);
        int q;
        scanf("%d", &q);
        while (q--) {
            int a, b, ans = 0x3f3f3f3f;
            scanf("%d%d", &a, &b);
            for (int x : office[a]) {
                for (int y : office[b]) {
                    int tmp = dist[x] + dist[y] - 2 * dist[lca(x, y)];
                    ans = min(ans, tmp);
                }
            }
            printf("%d\n", ans);
        }

        for (int i = 1; i <= max(n, m); ++i) {
            adj[i].clear();
            office[i].clear();
        }
    }

    return 0;
}

