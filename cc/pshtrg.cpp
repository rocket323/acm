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
const int maxl = 100010;
const int mod = 1e9 + 7;

struct node {
    int l, r, mx;
} nd[maxl * 4];

int n, m;
int a[maxl];

void build(int now, int l, int r) {
    nd[now].l = l, nd[now].r = r;
    nd[now].mx = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
    }
}

void change(int now, int l, int r, int v) {
    if (l <= nd[now].l && nd[now].r <= r) {
        nd[now].mx = v;
        return;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    if (l <= mid) change(now * 2, l, r, v);
    if (r > mid) change(now * 2 + 1, l, r, v);

    nd[now].mx = max(nd[now * 2].mx, nd[now * 2 + 1].mx);
}

int query(int now, int l, int r) {
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].mx;
    }
    int mid = (nd[now].l + nd[now].r) / 2;
    int lv = 0, rv = 0;
    if (l <= mid) lv = query(now * 2, l, r);
    if (r > mid) rv = query(now * 2 + 1, l, r);
    return lv + rv;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    build(1, 1, n);
    for (int i = 3; i <= n; i++) {
        if (a[i-2] + a[i-1] > a[i])
            change(1, i, i, a[i-2] + a[i-1] + a[i]);
    }

    for (int i = 0; i < m; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1) {
            a[x] = y;
            for (int j = i; j < i + 3; j++) {
                if (j < 3) continue;
                int v = 0;
                if (a[j-2] + a[j-1] > a[j])
                    v = a[j-2] + a[j-1] + a[j];
                change(1, j, j, v);
            }
        } else {
            int ans = 0;
            if (y - x + 1 >= 3)
                ans = query(1, x + 2, y);
            printf("%d\n", ans);
        }
    }

    return 0;
}

