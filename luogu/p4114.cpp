#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 1e5 + 10;
int n, k, e[maxl][3];
vector<int> adj[maxl];
int a[maxl], tot, u, v, x, y;
char op[10];

struct node {
    int l, r, mx;
} nd[maxl * 4];

void update(int now) {
    nd[now].mx = max(nd[now * 2].mx, nd[now * 2 + 1].mx);
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
        nd[now].mx = a[l];
    }
}

void change(int now, int l, int r, int val) {
    if (l <= nd[now].l && nd[now].r <= r) {
        nd[now].mx = val;
        return;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) change(now * 2, l, r, val);
    if (mid + 1 <= r) change(now * 2 + 1, l, r, val);
    update(now);
}

int qmax(int now, int l, int r) {
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].mx;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    int ans = 0;
    if (l <= mid) ans = max(ans, qmax(now * 2, l, r));
    if (mid < r) ans = max(ans, qmax(now * 2 + 1, l, r));
    return ans;
}

int sz[maxl], top[maxl], son[maxl], d[maxl], id[maxl], fa[maxl];
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

int query(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]])
            swap(u, v);
        ans = max(ans, qmax(1, id[top[u]], id[u]));
        u = fa[top[u]];
    }
    if (u == v)
        return ans;
    if (d[u] < d[v])
        swap(u, v);
    ans = max(ans, qmax(1, id[v] + 1, id[u]));
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
        adj[e[i][0]].push_back(e[i][1]);
        adj[e[i][1]].push_back(e[i][0]);
    }

    tot = 0;
    dfs1(1, 0, 0);
    dfs2(1, 1);

    memset(a, 0, sizeof(a));
    for (int i = 1; i < n; i++) {
        int u = e[i][0], v = e[i][1];
        if (d[u] < d[v])
            swap(u, v);
        a[id[u]] = e[i][2];
    }

    build(1, 1, n);

    while (true) {
        scanf("%s", op);
        if (strcmp(op, "QUERY") == 0) {
            scanf("%d%d", &u, &v);
            printf("%d\n", query(u, v));
        } else if (strcmp(op, "CHANGE") == 0) {
            scanf("%d%d", &x, &y);
            int u = e[x][0], v = e[x][1];
            if (d[u] < d[v]) swap(u, v);
            change(1, id[u], id[u], y);
        } else if (strcmp(op, "DONE") == 0) {
            break;
        }
    }
    return 0;
}
