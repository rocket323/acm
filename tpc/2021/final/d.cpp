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
    int sp, xp;
} ndx[maxl * 4], ndy[maxl * 4];

int n, m, p[maxl], e[maxl], c[maxl], rc[maxl];
int tp, te, t, rev;

bool cmp(const node1 &a, const node1 &b) {
    return a.a < b.a;
}

void build(node nd[], int now, int l, int r) {
    nd[now].l = l;
    nd[now].r = r;
    nd[now].sp = nd[now].xp = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        build(nd, now * 2, l, mid);
        build(nd, now * 2 + 1, mid + 1, r);
    }
}

void inc(int &a, int b) {
    a = (a + b % mod) % mod;
}

void add(node nd[], int now, int l, int r, int sp, int xp) {
    if (l <= nd[now].l && nd[now].r <= r) {
        inc(nd[now].sp, sp);
        inc(nd[now].xp, xp);
        return;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) add(nd, now * 2, l, r, sp, xp);
    if (r > mid) add(nd, now * 2 + 1, l, r, sp, xp);
    nd[now].sp = (nd[now*2].sp + nd[now*2+1].sp) % mod;
    nd[now].xp = (nd[now*2].xp + nd[now*2+1].xp) % mod;
}

void query(node nd[], int now, int l, int r, int &sp, int &xp) {
    if (l <= nd[now].l && nd[now].r <= r) {
        inc(sp, nd[now].sp);
        inc(xp, nd[now].xp);
        return;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) {
        query(nd, now * 2, l, r, sp, xp);
    }
    if (r > mid) {
        query(nd, now * 2 + 1, l, r, sp, xp);
    }
}

int pow(int a, int n) {
    int ans = 1, t = a;
    while (n) {
        if (n & 1) {
            ans = ((ll)ans * t) % mod;
        }
        t = ((ll)t * t) %mod;
        n >>= 1;
    }
    return ans;
}

void add(int j) {
    p[j] = ((ll)(1 + p[j]) * rc[j]) % mod;
    inc(tp, p[j]);
    inc(te, e[j]);

    add(ndx, 1, nd2[j].r, nd2[j].r, p[j], (ll)nd2[j].r * p[j] % mod);
    add(ndy, 1, nd2[j].c, nd2[j].c, p[j], (ll)nd2[j].c * p[j] % mod);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        int idx = 0;
        tp = te = 0;
        memset(e, 0, sizeof e);
        memset(p, 0, sizeof p);
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
        for (int i = tot-1; i>= 1; i--) {
            if (nd2[i].a == nd2[i+1].a)
                c[i] = c[i+1];
            else
                c[i] = c[i+1] + 1;

            rc[i] = pow(c[i], mod - 2);
        }
        for (int i = 1; i <= tot; i++) {
            // printf("%d %d\n", i, c[i]);
        }

        rev = pow(n * m, mod - 2);
        int last = 0, ans = 0;
        for (int i = 1; i <= tot; i++) {
            while (last + 1 <= tot && nd2[last+1].a < nd2[i].a) {
                add(last + 1);
                last++;
            }

            p[i] = (p[i] + tp) % mod;
            e[i] = (e[i] + te) % mod;

            int sumr = 0;
            int sp = 0, xp = 0;
            query(ndx, 1, nd2[i].r + 1, maxl, sp, xp);
            inc(sumr, mod + xp - (ll)nd2[i].r * sp % mod);

            sp = 0, xp = 0;
            query(ndx, 1, 0, nd2[i].r, sp, xp);
            inc(sumr, mod + (ll)nd2[i].r * sp - xp % mod);

            int sumc = 0;
            sp = 0;
            int yp = 0;
            query(ndy, 1, nd2[i].c + 1, maxl, sp, yp);
            inc(sumr, mod + yp - (ll)nd2[i].c * sp % mod);

            sp = 0, yp = 0;
            query(ndy, 1, 0, nd2[i].r, sp, yp);
            inc(sumr, mod + (ll)nd2[i].c * sp - yp % mod);

            inc(e[i], (sumr + sumc) % mod);

            if (nd2[i].a == nd2[tot].a) {
                inc(ans, e[i]);
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}

