#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 1e5 + 10;
int n, k, u, v, x, y, m;
vector<int> adj[maxl];

struct node {
    int l, r, lid;
} nd[maxl * 4];

void update(int now) {
    if (nd[now * 2].lid > 0)
        nd[now].lid = nd[now * 2].lid;
    else
        nd[now].lid = nd[now * 2 + 1].lid;
}

void build(int now, int l, int r) {
    nd[now].l = l;
    nd[now].r = r;
    if (l < r) {
        int mid = (l + r) / 2;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        update(now);
    } else {
        nd[now].lid = -1;
    }
}

void change(int now, int l, int r) {
    if (l <= nd[now].l && nd[now].r <= r) {
        nd[now].lid = (nd[now].lid > 0) ? -1 : nd[now].l;
        return;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) change(now * 2, l, r);
    if (mid < r) change(now * 2 + 1, l, r);
    update(now);
}

int query(int now, int l, int r) {
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].lid;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    int lv = -1, rv = -1;
    if (l <= mid) lv = query(now * 2, l, r);
    if (mid < r) rv = query(now * 2 + 1, l, r);
    if (lv != -1)
        return lv;
    else
        return rv;
}

int tot;
int sz[maxl], top[maxl], son[maxl], d[maxl], id[maxl], fa[maxl], rnk[maxl];
void dfs1(int u, int pre, int dep) {
    sz[u] = 1;
    fa[u] = pre;
    son[u] = 0;
    d[u] = dep;
    for (int v : adj[u]) {
        if (v != pre) {
            dfs1(v, u, dep + 1);
            sz[u] += sz[v];
            if (son[u] == 0 || sz[son[u]] < sz[v])
                son[u] = v;
        }
    }
}

void dfs2(int u, int tp) {
    id[u] = ++tot;
    top[u] = tp;
    if (son[u])
        dfs2(son[u], top[u]);

    for (int v : adj[u]) {
        if (v != fa[u] && v != son[u])
            dfs2(v, v);
    }
}

void update(int &ans, int tmp) {
    if (tmp == -1)
        return;
    if (ans == -1 || tmp < ans)
        ans = tmp;
}

void query1(int u) {
    int ans = -1;
    while (top[u] != top[1]) {
        int tmp = query(1, id[top[u]], id[u]);
        update(ans, tmp);
        u = fa[top[u]];
    }

    int tmp = query(1, id[1], id[u]);
    update(ans, tmp);
    printf("%d\n", ans == -1 ? -1 : rnk[ans]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    tot = 0;
    dfs1(1, 0, 0);
    dfs2(1, 1);
    build(1, 1, n);

    for (int i = 1; i <= n; i++) {
        rnk[id[i]] = i;
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &u);
        if (x == 0) {
            change(1, id[u], id[u]);
        } else {
            query1(u);
        }
    }

    return 0;
}
