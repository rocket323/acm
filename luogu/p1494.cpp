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
#include <cmath>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, m, a[maxl], cnt[maxl], bs;
ll ans;

struct Node {
    int l, r, idx;
    ll a, b;
} e[maxl];

bool cmp1(const Node &a, const Node &b) {
    int k1 = a.l / bs, k2 = b.l / bs;
    if (k1 != k2)
        return k1 < k2;
    return a.r < b.r;
}

ll f(int c) {
    return (ll)c * (c - 1) / 2;
}

void add(int k) {
    ans += f(cnt[k]+1) - f(cnt[k]);
    cnt[k]++;
}

void dec(int k) {
    ans += f(cnt[k]-1) - f(cnt[k]);
    cnt[k]--;
}

ll gcd(ll a, ll b) {
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        bs = sqrt(n) + 1;
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &e[i].l, &e[i].r);
            e[i].idx = i;
        }
        sort(e, e + m, cmp1);

        ans = 0;
        int l = 1, r = 1;
        add(a[1]);

        for (int i = 0; i < m; i++) {
            while (l > e[i].l) add(a[--l]);
            while (r < e[i].r) add(a[++r]);
            while (l < e[i].l) dec(a[l--]);
            while (r > e[i].r) dec(a[r--]);

            if (e[i].r == e[i].r) {
                e[i].a = 0;
                e[i].b = 1;
                continue;
            }

            ll total = (ll)(e[i].r - e[i].l + 1) * (e[i].r - e[i].l) / 2;
            ll d = gcd(total, ans);
            e[i].a = ans / d;
            e[i].b = total / d;
        }

        sort(e, e + m, [](const Node &a, const Node &b) { return a.idx < b.idx; });
        for (int i = 0; i < m; i++) {
            cout << e[i].a << '/' << e[i].b << endl;
        }
    }

    return 0;
}

