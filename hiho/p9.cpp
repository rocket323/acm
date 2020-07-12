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
const int maxl = (1 << 17) + 10;
const int mod = 1e9 + 7;
const ll INF = (1LL << 30);

int n, k, m;
int a[maxl];

struct node {
    int l, r;
    ll n_max, n_min;
    ll p_max, p_min;
} nd[maxl * 4];

void update(int now) {
    int lc = now * 2, rc = now * 2 + 1;

    nd[now].p_max = max(nd[lc].p_max, nd[rc].p_max);
    nd[now].p_min = min(nd[lc].p_min, nd[rc].p_min);

    nd[now].n_max = max(nd[lc].n_max, nd[rc].n_max);
    nd[now].n_min = min(nd[lc].n_min, nd[rc].n_min);
}

void build(int now, int l, int r) {
    nd[now].l = l, nd[now].r = r;
    nd[now].n_max = -INF;
    nd[now].n_min = INF;
    nd[now].p_max = -INF;
    nd[now].p_min = INF;

    if (l == r) {
        if (a[l] >= 0)
            nd[now].p_max = nd[now].p_min = a[l];
        else
            nd[now].n_max = nd[now].n_min = a[l];
    } else {
        int mid = (l + r) / 2;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        update(now);
    }
}

void change(int now, int l, int r, int val) {
    if (nd[now].l == nd[now].r) {
        nd[now].n_max = -INF;
        nd[now].n_min = INF;
        nd[now].p_max = -INF;
        nd[now].p_min = INF;

        if (val >= 0)
            nd[now].p_max = nd[now].p_min = val;
        else
            nd[now].n_max = nd[now].n_min = val;
        return;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) change(now * 2, l, r, val);
    if (r > mid) change(now * 2 + 1, l, r, val);

    update(now);
}

void get(int now, int l, int r, ll &p_min, ll &p_max, ll &n_min, ll &n_max) {
    if (l <= nd[now].l && nd[now].r <= r) {
        p_min = min(p_min, nd[now].p_min);
        p_max = max(p_max, nd[now].p_max);
        n_min = min(n_min, nd[now].n_min);
        n_max = max(n_max, nd[now].n_max);
        return;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid)
        get(now * 2, l, r, p_min, p_max, n_min, n_max);
    if (r > mid)
        get(now * 2 + 1, l, r, p_min, p_max, n_min, n_max);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &k);
        n = (1 << k);

        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);

        build(1, 0, n - 1);

        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            int p, x, y;
            scanf("%d%d%d", &p, &x, &y);

            if (p == 1) {
                ll p_min = INF, n_min = INF;
                ll p_max = -INF, n_max = -INF;

                get(1, x, y, p_min, p_max, n_min, n_max);
                vector<ll> v;
                if (p_min != INF) v.push_back(p_min);
                if (p_max != -INF) v.push_back(p_max);
                if (n_min != INF) v.push_back(n_min);
                if (n_max != -INF) v.push_back(n_max);

                ll ans = 1e17;
                for (int i = 0; i < v.size(); ++i)
                    for (int j = i; j < v.size(); ++j)
                        ans = min(ans, v[i] * v[j]);

                cout << ans << endl;
            } else {
                change(1, x, x, y);
            }
        }
    }

    return 0;
}

