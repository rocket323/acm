#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int t, n, q, a, b;
ll sum = 0;

struct node {
    int l, r;
    int flag, sum;
} nd[maxl * 4];

void build(int now, int l, int r) {
    nd[now].l = l, nd[now].r = r;
    nd[now].flag = nd[now].sum = 0;
    if (l < r) {
        int mid = (l + r) >> 1;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
    }
}

void pushDown(int now) {
    if (nd[now].flag == 0)
        return;

    if (nd[now].l < nd[now].r) {
        int lc = now * 2, rc = lc + 1;
        nd[lc].flag += nd[now].flag;
        nd[rc].flag += nd[now].flag;
    } else {
        nd[now].sum += nd[now].flag;
    }
    nd[now].flag = 0;
}

void add(int now, int l, int r, int v) {
    pushDown(now);
    if (l <= nd[now].l && nd[now].r <= r) {
        nd[now].flag += v;
        return;
    }
    int mid = (nd[now].l + nd[now].r) >> 1;
    if (l <= mid)
        add(now * 2, l, r, v);
    if (r > mid)
        add(now * 2 + 1, l, r, v);
}

int get(int now, int l, int r) {
    pushDown(now);
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].sum;
    }
    int mid = (nd[now].l + nd[now].r) >> 1;
    int lv = 0, rv = 0;
    if (l <= mid)
        lv = get(now * 2, l, r);
    if (r > mid)
        rv = get(now * 2 + 1, l, r);
    return lv + rv;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        sum = 0;
        scanf("%d%d", &n, &q);
        build(1, 0, n - 1);
        for (int i = 0; i < q; i++) {
            scanf("%d%d", &a, &b);
            sum = sum + a / n;
            a %= n;
            if (a == 0)
                continue;
            if (b + a - 1 < n) {
                add(1, b, b + a - 1, 1);
            } else {
                add(1, b, b + a - 1, 1);
                int x = a - (n - b);
                add(1, 0, x - 1, 1);
            }
        }
        for (int i = 0; i < n; i++) {
            ll ans = sum;
            ll x = get(1, i, i);
            ans += x;
            cout << ans;
            if (i == n - 1)
                cout << endl;
            else
                cout << ' ';
        }
    }
    return 0;
}
