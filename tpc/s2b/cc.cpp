#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;

int t, a[maxl];
int n;

struct node {
    int l, r;
    int p, g;
} nd[maxl * 4];

int gcd(int a, int b) {
    if (a < b) {
        swap(a, b);
    }
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void build(int now, int l, int r) {
    nd[now].l = l;
    nd[now].r = r;
    if (l < r) {
        int mid = (l + r) / 2;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);

        int p1 = nd[now * 2].p, p2 = nd[now * 2 + 1].p;
        nd[now].p = a[p1] < a[p2] ? p1 : p2;
        nd[now].g = gcd(nd[now * 2].g, nd[now * 2 + 1].g);
    } else {
        nd[now].p = l;
        nd[now].g = a[l];
    }
}

int getMin(int now, int l, int r) {
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].p;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    int p = -1;
    if (l <= mid) {
        p = getMin(now * 2, l, r);
    }

    if (r > mid) {
        int pp = getMin(now * 2 + 1, l, r);
        if (p == -1 || a[pp] < a[p])
            p = pp;
    }

    return p;
}

int getGcd(int now, int l, int r) {
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].g;
    }

    int mid = (nd[now].l + nd[now].r) / 2;
    int g = -1;
    if (l <= mid) {
        g = getGcd(now * 2, l, r);
    }

    if (r > mid) {
        int gg = getGcd(now * 2 + 1, l, r);
        if (g == -1)
            g = gg;

        g = gcd(g, gg);
    }

    return g;
}

bool check(int l, int r) {
    if (l == r) {
        return true;
    }

    int p = getMin(1, l, r);
    int g = a[p];
    if (l < p) {
        g = gcd(g, getGcd(1, l, p - 1));
        if (!check(l, p - 1))
            return false;
    }

    if (p < r) {
        g = gcd(g, getGcd(1, p + 1, r));
        if (!check(p + 1, r))
            return false;
    }

    if (g != a[p])
        return false;

    return true;
}

bool solve() {
    return check(1, n);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        build(1, 1, n);
        puts(solve() ? "Yes" : "No");
    }

    return 0;
}
