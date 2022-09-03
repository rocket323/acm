#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int BS = 0;
int c1[35], n, m;
int a[maxl];

struct node {
    int l, r, idx;
    unsigned ans;
} e[maxl];

bool cmp1(const node &a, const node &b) {
    int b1 = a.l / BS, b2 = b.l / BS;
    if (b1 != b2)
        return b1 < b2;
    return a.r < b.r;
}

bool cmp2(const node &a, const node &b) {
    return a.idx < b.idx;
}

void add(int p, int v) {
    int num = a[p], idx = 0;
    while (num) {
        if (num & 1)
            c1[idx] += v;
        idx++;
        num >>= 1;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    BS = sqrt(n) + 10;

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &e[i].l, &e[i].r);
        e[i].l--;
        e[i].r--;
        e[i].idx = i;
    }

    sort(e, e + m, cmp1);
    memset(c1, 0, sizeof c1);

    int l = 0, r = 0;
    add(0, 1);
    for (int i = 0; i < m; i++) {
        auto &q = e[i];
        while (l > q.l)
            add(--l, 1);
        while (r < q.r)
            add(++r, 1);
        while (l < q.l)
            add(l++, -1);
        while (r > q.r)
            add(r--, -1);

        unsigned ans = 0, tot = r - l + 1;
        for (int j = 0; j < 31; j++) {
            int cc1 = c1[j], cc0 = tot - c1[j];
            if (cc0 > cc1)
                ans = ans + (1 << j);
        }
        q.ans = ans;
    }

    sort(e, e + m, cmp2);
    for (int i = 0; i < m; i++)
        printf("%d\n", e[i].ans);

    return 0;
}
