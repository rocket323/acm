#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int t, n, m;
struct Query {
    int t, l, r;
} e[maxl];

struct node {
    int l, r;
    int flag, sum;
} nd1[maxl * 4], nd2[maxl * 4];

void build(node nd[], int now, int l, int r) {
    nd[now].l = l, nd[now].r = r;
    nd[now].flag = nd[now].sum = 0;
    if (l < r) {
        int mid = (l + r) >> 1;
        build(nd, now * 2, l, mid);
        build(nd, now * 2 + 1, mid + 1, r);
    }
}

int inc(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

void pushDown(node nd[], int now) {
    if (nd[now].flag == 0) return;

    if (nd[now].l < nd[now].r) {
        int lc = now * 2, rc = lc + 1;
        inc(nd[lc].flag, nd[now].flag);
        inc(nd[rc].flag, nd[now].flag);
    } else {
        inc(nd[now].sum, nd[now].flag);
    }
    nd[now].flag = 0;
}

void add(node nd[], int now, int l, int r, int v) {
    pushDown(nd, now);
    if (l <= nd[now].l && nd[now].r <= r) {
        inc(nd[now].flag, v);
        return;
    }
    int mid = (nd[now].l + nd[now].r) >> 1;
    if (l <= mid) add(nd, now * 2, l, r, v);
    if (r > mid) add(nd, now * 2 + 1, l, r, v);
}

int get(node nd[], int now, int l, int r) {
    pushDown(nd, now);
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].sum;
    }
    int mid = (nd[now].l + nd[now].r) >> 1;
    int lv = 0, rv = 0;
    if (l <= mid) lv = get(nd, now * 2, l, r);
    if (r > mid) rv = get(nd, now * 2 + 1, l, r);
    return inc(lv, rv);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
            scanf("%d%d%d", &e[i].t, &e[i].l, &e[i].r);

        build(nd2, 1, 1, m);
        add(nd2, 1, 1, m, 1);
        for (int i = m; i >= 1; --i) {
            if (e[i].t == 1) continue;
            int num = get(nd2, 1, i, i);
            add(nd2, 1, e[i].l, e[i].r, num);
        }

        build(nd1, 1, 1, n);
        for (int i = 1; i <= m; ++i) {
            if (e[i].t == 2) continue;
            int num = get(nd2, 1, i, i);
            add(nd1, 1, e[i].l, e[i].r, num);
        }

        for (int i = 1; i <= n; ++i) {
            int num = get(nd1, 1, i, i);
            printf("%d%c", num, (i == n) ? '\n' : ' ');
        }
    }

    return 0;
}

