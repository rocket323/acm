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
using namespace std;

typedef long long ll;
const ll maxl = 400010;
const ll mod = 1e9 + 7;

ll n, q;
vector<pair<ll, ll>> adj[maxl];

ll sz[maxl], top[maxl], son[maxl], dep[maxl], id[maxl], pre[maxl];
ll tot, tot2;
ll b1[maxl], bp[maxl];
ll left[maxl], right[maxl];
ll v[maxl], dist[maxl];
ll v2[maxl];

struct Edge {
    ll u, v;
} ed[maxl * 2 + 10];

struct node {
    ll l, r;
    ll sum;
} nd[maxl * 4];

void update(ll now) {
    nd[now].sum = nd[now * 2].sum + nd[now * 2 + 1].sum;
}

void build(ll now, ll l, ll r) {
    nd[now].l = l, nd[now].r = r;
    nd[now].sum = 0;
    if (l == r) {
        nd[now].sum = v[l];
    } else {
        ll mid = (l + r) / 2;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        update(now);
    }
}

void change(ll now, ll l, ll r, ll val) {
    if (l <= nd[now].l && nd[now].r <= r) {
        nd[now].sum = val;
        return;
    }
    ll mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) change(now * 2, l, r, val);
    if (r > mid) change(now * 2 + 1, l, r, val);

    update(now);
}

ll query(ll now, ll l, ll r) {
    if (l <= nd[now].l && nd[now].r <= r)
        return nd[now].sum;
    ll mid = (nd[now].l + nd[now].r) / 2;
    ll lv = 0, rv = 0;
    if (l <= mid) lv += query(now * 2, l, r);
    if (r > mid) rv += query(now * 2 + 1, l, r);
    return lv + rv;
}

struct node2 {
    int l, r;
    ll mx, buf;
}nd2[maxl * 4];

void pushDown(int now) {
    if (nd2[now].buf == 0) return;
    ll buf = nd2[now].buf;
    nd2[now].mx += buf;
    nd2[now].buf = 0;
    if (nd2[now].l == nd2[now].r) return;

    nd2[now * 2].buf += buf;
    nd2[now * 2 + 1].buf += buf;
}

void pushUp(int now) {
    pushDown(now * 2);
    pushDown(now * 2 + 1);
    nd2[now].mx = min(nd2[now * 2].mx, nd2[now * 2 + 1].mx);
}

void build2(int now, int l, int r) {
    nd2[now].l = l, nd2[now].r = r;
    nd2[now].buf = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        build2(now * 2, l, mid);
        build2(now * 2 + 1, mid + 1, r);
        pushUp(now);
    } else {
        nd2[now].mx = v2[l];
    }
}

void add(int now, int l, int r, ll v) {
    pushDown(now);
    if (l <= nd2[now].l && nd2[now].r <= r) {
        nd2[now].buf += v;
        return;
    }
    int mid = (nd2[now].l + nd2[now].r) / 2;
    if (l <= mid) add(now * 2, l, r, v);
    if (r > mid) add(now * 2 + 1, l, r, v);

    pushUp(now);
}

ll get(int now, int l, int r) {
    pushDown(now);
    if (l <= nd2[now].l && nd2[now].r <= r) {
        return nd2[now].mx;
    }
    int mid = (nd2[now].l + nd2[now].r) / 2;
    ll lv = 1e16, rv = 1e16;
    if (l <= mid) lv = get(now * 2, l, r);
    if (r > mid) rv = get(now * 2 + 1, l, r);
    return min(lv, rv);
}

void dfs1(ll u, ll p, ll d) {
    sz[u] = 1;
    pre[u] = p;
    son[u] = 0;
    dep[u] = d;

    for (auto &pp : adj[u]) {
        ll v = pp.first;
        if (v != p) {
            bp[v] = pp.second;
            dist[v] = dist[u] + pp.second;
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if (son[u] == 0 || sz[son[u]] < sz[v])
                son[u] = v;
        }
    }
}

void dfs2(ll u, ll tp) {
    ::left[u] = tot2++;
    id[u] = tot++;
    top[u] = tp;

    if (son[u])
        dfs2(son[u], top[u]);

    for (auto &pp : adj[u]) {
        ll v = pp.first;
        if (v != pre[u] && v != son[u])
            dfs2(v, v);
    }

    ::right[u] = tot2++;
}

ll solve(ll u) {
    ll ans = 0;
    while (u != 1 && u != 0) {
        ll fu = top[u];
        if (fu != u)
            ans += query(1, id[fu] + 1, id[u]);
        if (fu != 1)
            ans += bp[fu];
        u = pre[fu];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q;
    memset(b1, 0, sizeof b1);
    memset(bp, 0, sizeof bp);
    memset(nd, 0, sizeof nd);
    dist[1] = 0;
    for (ll i = 1; i <= n; ++i)
        adj[i].clear();
    for (ll i = 1; i <= 2 * n - 2; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        ed[i].u = u;
        ed[i].v = v;
        if (i <= n - 1)
            adj[u].push_back(make_pair(v, w));
        else {
            b1[u] = w;
        }
    }

    tot = 1;
    tot2 = 1;
    dfs1(1, 0, 0);
    dfs2(1, 1);

    for (ll i = 1; i <= n; ++i) {
        v[id[i]] = bp[i];
    }

    build(1, 1, n);

    for (int i = 1; i <= n; ++i) {
        v2[::left[i]] = b1[i] + dist[i];
        v2[::right[i]] = b1[i] + dist[i];
    }
    build2(1, 1, 2 * n);

    for (ll i = 0; i < q; ++i) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll k, t, u, v;
            cin >> k >> t;
            u = ed[k].u, v = ed[k].v;
            if (k > n - 1) {
                int sb1 = b1[u];
                b1[u] = t;
                add(1, ::left[u], ::left[u], b1[u] - sb1);
                add(1, ::right[u], ::right[u], b1[u] - sb1);
            } else {
                if (dep[u] > dep[v]) swap(u, v);
                ll tu = top[u], tv = top[v];
                int sbp = bp[v];
                if (tu == tv) {
                    change(1, id[v], id[v], t);
                    bp[v] = t;
                } else {
                    bp[v] = t;
                }
                add(1, ::left[v], ::right[v], bp[v] - sbp);
            }
        } else {
            ll u, v;
            cin >> u >> v;
            ll ans = 0;
            if (v != u) {
                if (::left[u] <= ::left[v] && ::left[v] <= ::right[u]) {
                    ans = solve(v) - solve(u);
                } else {
                    ll sv = solve(v);
                    ans = sv + b1[u];

                    ll tmp = get(1, ::left[u], ::right[u]);
                    tmp = tmp - solve(u) + sv;
                    ans = min(ans, tmp);
                }
            }
            cout << ans << endl;
        }
    }

    return 0;
}

