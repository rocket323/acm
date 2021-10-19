#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;
const int mod = 1e9 + 7;

struct node1 {
    int r, c, a;
} nd2[maxl];

struct node {
    int l, r;
    int x, cnt;
} ndx[maxl * 4], ndy[maxl * 4];

int n, m, e[maxl], c[maxl], rc[maxl];
int tp, te, t, rev;

bool cmp(const node1 &a, const node1 &b) {
    return a.a < b.a;
}

void build(node nd[], int now, int l, int r) {
    nd[now].l = l;
    nd[now].r = r;
    nd[now].x = 0;
    nd[now].cnt = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        build(nd, now * 2, l, mid);
        build(nd, now * 2 + 1, mid + 1, r);
    }
}

void inc(int &a, int b) {
    a = (a + b % mod) % mod;
}

void add(node nd[], int now, int l, int r, int x) {
    if (l <= nd[now].l && nd[now].r <= r) {
        inc(nd[now].x, x);
        inc(nd[now].cnt, 1);
        return;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid)
        add(nd, now * 2, l, r, x);
    if (r > mid)
        add(nd, now * 2 + 1, l, r, x);
    nd[now].x = (nd[now * 2].x + nd[now * 2 + 1].x) % mod;
    nd[now].cnt = (nd[now * 2].cnt + nd[now * 2 + 1].cnt) % mod;
}

void query(node nd[], int now, int l, int r, int &x, int &c) {
    if (l <= nd[now].l && nd[now].r <= r) {
        inc(x, nd[now].x);
        inc(c, nd[now].cnt);
        return;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) {
        query(nd, now * 2, l, r, x, c);
    }
    if (r > mid) {
        query(nd, now * 2 + 1, l, r, x, c);
    }
}

int pow(int a, int n) {
    int ans = 1, t = a;
    while (n) {
        if (n & 1) {
            ans = ((ll)ans * t) % mod;
        }
        t = ((ll)t * t) % mod;
        n >>= 1;
    }
    return ans;
}

void add(int j) {
    inc(te, e[j]);

    add(ndx, 1, nd2[j].r, nd2[j].r, (ll)nd2[j].r);
    add(ndy, 1, nd2[j].c, nd2[j].c, (ll)nd2[j].c);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        int idx = 0;
        tp = te = 0;
        memset(e, 0, sizeof e);
        build(ndx, 1, 0, maxl);
        build(ndy, 1, 0, maxl);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                idx++;
                scanf("%d", &nd2[idx].a);
                nd2[idx].r = i;
                nd2[idx].c = j;
            }
        }
        int tot = idx;
        sort(nd2 + 1, nd2 + tot + 1, cmp);

        c[tot] = 0;
        rc[tot] = 0;
        for (int i = tot - 1; i >= 1; i--) {
            if (nd2[i].a == nd2[i + 1].a)
                c[i] = c[i + 1];
            else
                c[i] = c[i + 1] + 1;

            rc[i] = pow(c[i], mod - 2);
        }

        int last = tot + 1, ans = 0;
        for (int i = tot; i >= 1; i--) {
            while (last - 1 > i && nd2[last - 1].a > nd2[i].a) {
                add(last - 1);
                last--;
            }

            if (c[i] == 0)
                continue;

            int pi = rc[i];
            int sum = te;
            int sx = 0, sc = 0;
            query(ndx, 1, nd2[i].r + 1, maxl, sx, sc);
            inc(sum, mod + sx - (ll)sc * nd2[i].r % mod);

            sx = 0, sc = 0;
            query(ndx, 1, 0, nd2[i].r, sx, sc);
            inc(sum, mod + (ll)sc * nd2[i].r % mod - sx);

            sx = 0, sc = 0;
            query(ndy, 1, nd2[i].c + 1, maxl, sx, sc);
            inc(sum, mod + sx - (ll)sc * nd2[i].c % mod);

            sx = 0, sc = 0;
            query(ndy, 1, 0, nd2[i].c, sx, sc);
            inc(sum, mod + (ll)sc * nd2[i].c % mod - sx);

            e[i] = (ll)pi * sum % mod;
            inc(ans, e[i]);
        }

        printf("%d\n", ans);
    }
    return 0;
}
