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

int n, a[maxl];
ll ls[maxl];

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
    if (nd[now].flag == 0) return;

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
    if (l <= mid) add(now * 2, l, r, v);
    if (r > mid) add(now * 2 + 1, l, r, v);
}

int get(int now, int l, int r) {
    pushDown(now);
    if (l <= nd[now].l && nd[now].r <= r) {
        return nd[now].sum;
    }
    int mid = (nd[now].l + nd[now].r) >> 1;
    int lv = 0, rv = 0;
    if (l <= mid) lv = get(now * 2, l, r);
    if (r > mid) rv = get(now * 2 + 1, l, r);
    return lv + rv;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(ls, 0, sizeof ls);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            ls[i] = ls[i - 1] + a[i];
        }

        build(1, 1, n);

        for (int i = 1; i <= n; i++) {
            int l = 1, r = i - 1, lidx = i, ridx = i;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (ls[i-1] - ls[mid-1] <= a[i]) {
                    lidx = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }

            l = i + 1;
            r = n;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (ls[mid] - ls[i] <= a[i]) {
                    ridx = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            if (lidx > 1) lidx--;
            if (lidx < i) {
                add(1, lidx, i - 1, 1);
            }
            if (ridx < n) ridx++;
            if (ridx > i) {
                add(1, i + 1, ridx, 1);
            }
        }

        for (int i = 1; i <= n; i++) {
            int v = get(1, i, i);
            printf("%d%c", v, (i == n) ? '\n' : ' ');
        }
    }

    return 0;
}

