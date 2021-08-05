#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;
int t, n, u, v;
int f[maxl][21], d[maxl], p[maxl];
vector<int> adj[maxl];
int a[maxl], vis[maxl], ans[maxl];

void dfs(int u, int pre) {
    d[u] = d[pre] + 1;
    f[u][0] = pre;
    for (int i = 1; i < 20; i++) {
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != pre) {
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (d[u] < d[v])
        swap(u, v);
    for (int i = 19; i >= 0; i--) {
        if (d[f[u][i]] >= d[v])
            u = f[u][i];
    }
    if (u == v)
        return u;
    for (int i = 19; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

bool cmp(int i, int j) {
    return a[i] > a[j];
}

int dist(int u, int v) {
    int x = lca(u, v);
    return d[u] + d[v] - d[x] * 2;
}

struct Dia {
    int x, y, len;
    Dia() {
    }
    Dia(int _x, int _y) : x(_x), y(_y), len(dist(_x, _y)) {
    }
    Dia(int _x, int _y, int _len) : x(_x), y(_y), len(_len) {
    }
    bool operator<(Dia b) const {
        return len < b.len;
    }
    Dia operator+(Dia b) {
        return max({*this, b, Dia(x, b.x), Dia(x, b.y), Dia(y, b.x), Dia(y, b.y)});
    }
} di[maxl];

int pre[maxl];

int root(int x) {
    return pre[x] == x ? x : pre[x] = root(pre[x]);
}

void merge1(int u, int v) {
    u = root(u);
    v = root(v);
    if (u != v) {
        pre[u] = v;
        di[v] = di[v] + di[u];
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            adj[i].clear();
            p[i] = i;
            pre[i] = i;
        }
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        d[0] = -1;
        dfs(1, 0);

        sort(p + 1, p + n + 1, cmp);
        memset(vis, 0, sizeof(vis));
        memset(ans, 0, sizeof(ans));
        for (int i = 1; i <= n; i++) {
            int u = p[i];
            vis[u] = 1;
            di[u] = Dia(u, u, 0);
            for (int v : adj[u]) {
                if (vis[v]) {
                    merge1(u, v);
                }
            }

            int len = di[root(u)].len + 1;
            ans[len] = max(ans[len], a[u]);
        }

        for (int i = n - 1; i >= 1; i--) {
            ans[i] = max(ans[i], ans[i + 1]);
        }

        for (int i = 1; i <= n; i++) {
            printf("%d%c", ans[i], i == n ? '\n' : ' ');
        }
    }

    return 0;
}
