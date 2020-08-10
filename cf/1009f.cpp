#include <bits/stdc++.h>

using namespace std;

const int maxl = 1e6 + 10;
int n, m, ans[maxl], d[maxl], sz[maxl], son[maxl];
vector<int> adj[maxl];

int cnt[maxl];

struct Node {
    int c;
    int d;
};

bool operator<(const Node &a, const Node &b) {
    if (a.c != b.c)
        return a.c > b.c;
    return a.d < b.d;
}

set<Node> mp;

void dfs1(int u, int fa, int dep) {
    d[u] = dep;
    sz[u] = 1;
    son[u] = 0;

    for (int v : adj[u]) {
        if (v == fa)
            continue;

        dfs1(v, u, dep + 1);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}

void add(int u, int val, int fa, int son) {
    int dd = d[u];
    Node old = {cnt[dd], dd};
    mp.erase(old);
    if (val > 0) {
        Node nw = {cnt[dd] + 1, dd};
        mp.insert(nw);
    } else {
        if (cnt[dd] - 1 > 0) {
            Node nw = {cnt[dd] - 1, dd};
            mp.insert(nw);
        }
    }

    cnt[dd] += val;

    for (int v : adj[u]) {
        if (v != fa && v != son)
            add(v, val, u, son);
    }
}

void dfs2(int u, int fa, int keep) {
    for (int v : adj[u]) {
        if (v != fa && v != son[u])
            dfs2(v, u, 0);
    }

    if (son[u])
        dfs2(son[u], u, 1);

    add(u, 1, fa, son[u]);

    int dd = mp.begin()->d;
    ans[u] = dd - d[u];

    if (!keep) {
        add(u, -1, fa, 0);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++)
            adj[i].clear();

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs1(1, 0, 0);
        dfs2(1, 0, 0);

        for (int i = 1; i <= n; i++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
