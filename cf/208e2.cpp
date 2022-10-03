#include <stdio.h>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;
using uii = unordered_map<int, int>;

const int maxl = 1e5 + 10;
int n, m, p, v, k;
vector<int> adj[maxl];
int sz[maxl], son[maxl], d[maxl];
int f[maxl][20], cnt[maxl];

struct query {
    int k, ans;
} q[maxl];

vector<query *> e[maxl];

void dfs1(int u, int fa, int dep) {
    d[u] = dep;
    sz[u] = 1;
    son[u] = 0;
    f[u][0] = fa;

    for (int i = 1; i < 20; i++) {
        f[u][i] = f[f[u][i - 1]][i - 1];
    }

    for (int v : adj[u]) {
        dfs1(v, u, dep + 1);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

int getFa(int u, int d) {
    for (int i = 19; i >= 0; i--) {
        if (d & (1 << i)) {
            u = f[u][i];
        }
    }
    return u;
}

void merge(uii &h, uii &l) {
    for (auto &&[k, v] : l) {
        h[k] += v;
    }
}

uii dfs2(int u) {
    uii h;
    if (son[u]) {
        h = dfs2(son[u]);
    }
    for (int v : adj[u]) {
        if (v != son[u]) {
            uii l = dfs2(v);
            merge(h, l);
        }
    }
    uii self = {{d[u], 1}};
    merge(h, self);

    for (auto &q : e[u]) {
        int dep = d[u] + q->k;
        q->ans = h[dep] - 1;
    }
    return h;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p);
        adj[p].push_back(i);
    }

    dfs1(0, 0, 0);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &v, &k);
        q[i].k = k;
        int u = getFa(v, k);
        if (u == 0) {
            q[i].ans = 0;
        } else {
            e[u].push_back(&q[i]);
        }
    }

    dfs2(0);

    for (int i = 1; i <= m; i++) {
        printf("%d%c", q[i].ans, i == m ? '\n' : ' ');
    }

    return 0;
}
