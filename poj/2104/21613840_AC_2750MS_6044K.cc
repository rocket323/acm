#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
const int maxl = 105010;
const int mod = 1e9 + 7;
const int inf = 1e9 + 10;

struct Node {
    int type;
    int pos, val;
    int l, r, k;
} q[maxl], q1[maxl], q2[maxl];

int n, m, top, ans[maxl];
int c[maxl + 10];

void add(int n, int val) {
    for (n += 2; n < maxl; n += n & -n)
        c[n] += val;
}

int query(int n) {
    int ans = 0;
    for (n += 2; n; n -= n & -n)
        ans += c[n];
    return ans;
}

void solve(int l, int r, int L, int R) {
    if (l > r || L > R)
        return;

    if (l == r) {
        for (int i = L; i <= R; i++) {
            if (q[i].type)
                ans[q[i].pos] = l;
        }
        return;
    }

    int mid = (l + r) >> 1, top1 = 0, top2 = 0;
    for (int i = L; i <= R; i++) {
        if (q[i].type == 1) {
            int cnt = query(q[i].r) - query(q[i].l - 1);
            if (q[i].k <= cnt) {
                q1[top1++] = q[i];
            } else {
                q[i].k -= cnt;
                q2[top2++] = q[i];
            }
        } else {
            if (q[i].val <= mid) {
                q1[top1++] = q[i];
                add(q[i].pos, 1);
            } else {
                q2[top2++] = q[i];
            }
        }
    }

    for (int i = 0; i < top1; i++) {
        if (q1[i].type == 0)
            add(q1[i].pos, -1);
    }

    int idx = L;
    for (int i = 0; i < top1; i++)
        q[idx++] = q1[i];
    for (int i = 0; i < top2; i++)
        q[idx++] = q2[i];

    solve(l, mid, L, L + top1 - 1);
    solve(mid + 1, r, L + top1, R);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        top = 0;
        int mx = -inf, mn = inf;
        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);
            q[top++] = {0, i, a, 0, 0, 0};
            mx = max(mx, a);
            mn = min(mn, a);
        }

        for (int i = 0; i < m; i++) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            q[top++] = {1, i, 0, l, r, k};
        }

        solve(mn, mx, 0, top - 1);
        for (int i = 0; i < m; i++)
            printf("%d\n", ans[i]);
    }

    return 0;
}
